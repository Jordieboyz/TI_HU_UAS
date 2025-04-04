#include "esp8266.h"

#include "modules.h"

//========================================
//              PUBLIC
//=======================================

ESP8266::ESP8266(HW_UART *_serial) : serial_(_serial) {}

// TESTME: proposed void* way to receive arbitary data
// TODO: Add timeout to fix desync
return_data_s *ESP8266::ReceiveVoid(){
  int size = 0;
  while (true){
    if (serial_->GetChar() == ':'){
      size = serial_->GetInt();
      for (int i = 0; i < size; i++){
        ints[i] = serial_->GetInt();
      }
      break;
    }
  }
  rvoid_.data = (void *)ints;
  rvoid_.size = size;
  return &rvoid_;
}

// TESTME: proposed void* way to send arbitary data
EXIT ESP8266::SendVoid(void *data, int size){
  char *data_char = static_cast<char *>(data);
  params p[2] = {{intoa(kCh, buff_, dec), false},
                 {intoa(size+1, buff2_, dec), false}};

  if (size >= 128){
    return EXIT::FAILURE; // max size of message to avoid overflow on receiving
                          // side.
  }

  if (SendCommand(cmdmap[CIPSEND], p, (sizeof(p) / sizeof(*p)))){
    serial_->PutInt(size); // we need to know the length of the message

    for (int i = 0; i < size; i++){
      serial_->PutInt(data_char[i]);
    } 
  }
  return WaitResponse();
}

EXIT ESP8266::InitEspClient(const char *ssid, const char *pwd){
  Init();
  SetWifiMode(1);
  EnableMultipleConnections(1);

  if (ConnectToAP(ssid, pwd)){
    return EXIT::SUCCES;
  } else {
    return EXIT::FAILURE;
  }
}

EXIT ESP8266::InitEspSoftAccessPoint(const char *ssid, const char *pwd, int port){
  Init();
  SetWifiMode(3);
  EnableMultipleConnections(1);
  SetLocalIp("192.168.4.1", "192.168.4.1", "255.255.255.0");
  ConfigureAP(ssid, pwd, 1, 2, 2);
  return CreateServer(1, port);
}

//========================================
//              PRIVATE
//========================================

void ESP8266::Init()
{
  Reset();
  hwlib::wait_ms(4000);
  
  CheckStarted();
  SetWifiPower(79);
  DisconnectFromAP();
  DisconnectClients();
}

EXIT ESP8266::CheckStarted() { return SendCommand(cmdmap[AT]); }

EXIT ESP8266::Reset() { return SendCommand(cmdmap[RST]); }

EXIT ESP8266::DisconnectFromAP() { return SendCommand(cmdmap[CWQAP]); }

EXIT ESP8266::FactoryReset() { return SendCommand(cmdmap[RESTORE]); }

EXIT ESP8266::ShowAvailableAPs() { return SendCommand(cmdmap[CWLAP]); }

EXIT ESP8266::GetConnectedIPs() { return SendCommand(cmdmap[CWLIF]); }

EXIT ESP8266::DisconnectClients() { return SendCommand(cmdmap[CWQIF]); }

EXIT ESP8266::GetConnectionStatus() { return SendCommand(cmdmap[CIPSTATUS]); }

EXIT ESP8266::CloseConnection() { return SendCommand(cmdmap[CIPCLOSE]); }

EXIT ESP8266::GetLocalIP() { return SendCommand(cmdmap[CIFSR]); }

EXIT ESP8266::SetTransmissionMode(bool mode)
{
  params p[1] = {{intoa(mode, buff_, dec), false}};
  return SendCommand(cmdmap[CIPMODE], p);
}

EXIT ESP8266::SetLocalIp(const char *ip, const char *gateway,
                         const char *netmask){
  if (!ip || *ip == '\0'){
    return EXIT::FAILURE;
  }

  if (!gateway || !netmask){
    return EXIT::FAILURE;
  }

  if (*gateway == '\0'){
    gateway = nullptr;
  }

  if (*netmask == '\0'){
    netmask = nullptr;
  }

  params p[3] = {{ip, true}, {gateway, true}, {netmask, true}};
  return SendCommand(cmdmap[CIPAP], p, (sizeof(p) / sizeof(*p)));
}

EXIT ESP8266::CreateServer(bool mode, int port){
  if (port > 0){
    params p[2] = {{intoa(mode, buff_, dec), false},
                   {intoa(port, buff2_, dec), false}};
    return SendCommand(cmdmap[CIPSERVER], p, sizeof(p) / sizeof(*p));
  } else {
    return EXIT::FAILURE;
  }
}

EXIT ESP8266::SetWifiPower(int power){
  if (power > 40){
    params p[1] = {{intoa(std::min(power, 82), buff_, dec), false}};
    return SendCommand(cmdmap[RFPOWER], p);
  } else {
    return EXIT::FAILURE;
  }
}

EXIT ESP8266::EnableEcho(bool mode){
  if (mode){
    return SendCommand(cmdmap[ATE1]);
  } else {
    return SendCommand(cmdmap[ATE0]);
  }
}

EXIT ESP8266::ConfigureAP(const char *ssid, const char *pwd, int chl, int ecn,
                          int maxconn, bool ssid_hidden){
  if (!ssid || *ssid == '\0' || strlen(ssid) > 32){
    return EXIT::FAILURE;
  }

  if (pwd && !(strlen(pwd) < 64 && strlen(pwd) >= 8)){
    return EXIT::FAILURE;
  }

  if (chl >= 0){
    chl = std::min(20, chl);
  } else {
    return EXIT::FAILURE;
  }

  if (!(ecn >= 0 && ecn < 5)){
    return EXIT::FAILURE;
  }

  if (!(maxconn > 0 && maxconn < 11)){
    return EXIT::FAILURE;
  }

  struct ap_conf conf;
  conf.ssid = ssid;
  conf.channel = chl;
  conf.maxconn = maxconn;
  conf.ecn = ecn;
  conf.ssid_hidden = ssid_hidden;

  if (!conf.ecn){
    conf.pwd = "\0";
  } else {
    conf.pwd = pwd;
  }

  char buff3[4];
  char buff4[4];
  params p[] = {{conf.ssid, true},
                {conf.pwd, true},
                {intoa(conf.channel, buff_, dec), false},
                {intoa(conf.ecn, buff2_, dec)},
                {intoa(conf.maxconn, buff3, dec)},
                {intoa(conf.ssid_hidden, buff4, dec)}};

  return SendCommand(cmdmap[CWSAP], p, (sizeof(p) / sizeof(*p)));
}

EXIT ESP8266::StartTCPconnection(const char *remote_host, int port){
  if (!remote_host || *remote_host == '\0'){
    return EXIT::FAILURE;
  }

  if (port < 0){
    return EXIT::FAILURE;
  }

  params p[4] = {{intoa(kCh, buff_, dec), false},
                 {"TCP", true},
                 {remote_host, true},
                 {intoa(port, buff2_, dec), false}};
  return SendCommand(cmdmap[CIPSTART], p, (sizeof(p) / sizeof(*p)));
}

EXIT ESP8266::EnableMultipleConnections(bool multiconn){
  params p = {intoa(multiconn, buff_, dec), false};
  return SendCommand(cmdmap[CIPMUX], &p);
}

EXIT ESP8266::SetWifiMode(int mode, bool autoconn){
  if (mode < 0 || mode > 3){
    return EXIT::FAILURE;
  }

  params p[2] = {{intoa(mode, buff_, dec), false},
                 {intoa(autoconn, buff2_, dec), false}};
  return SendCommand(cmdmap[CWMODE], p);
}

EXIT ESP8266::ConnectToAP(const char *ssid, const char *pwd, const char *bssid){
  if (!ssid || *ssid == '\0' || strlen(ssid) > 32){
    return EXIT::FAILURE;
  }

  if (!pwd || strlen(pwd) > 63){
    return EXIT::FAILURE;
  }

  if (!bssid){
    return EXIT::FAILURE;
  }

  struct ap_conct connect;
  connect.ssid = ssid;
  connect.pwd = pwd;
  connect.chl = kCh;

  if (*bssid == '\0'){
    connect.bssid = nullptr;
  } else {
    connect.bssid = bssid;
  }

  params p[3] = {{connect.ssid, true}, {connect.pwd, true}, {connect.bssid, true}};
  return SendCommand(cmdmap[CWJAP], p, (sizeof(p) / sizeof(*p)));
}

EXIT ESP8266::Ping(const char *remote_host){
  if (!remote_host || *remote_host == '\0'){
    return EXIT::FAILURE;
  }
  
  params p = {remote_host, true};
  return SendCommand(cmdmap[PING], &p);
}

EXIT ESP8266::SendCommand(const char *command, params *p, unsigned int n){
  int lenCmd = strlen(command) + 1;
  char paramBuffer[128] = "";

  for (params *it = p; it != (p + n); ++it){
    if (!it->str && (it == (p + (n - 1)))){
      continue;
    } else {
      if (it == p){
        strcat(paramBuffer, "=");
      } else {
        strcat(paramBuffer, ",");
      }
    }

    if (!it->str){
      continue;
    }

    lenCmd += strlen(it->str);
    if (!it->strCheck){
      strcat(paramBuffer, it->str);
    } else {
      strcat(strcat(strcat(paramBuffer, "\""), it->str), "\"");
    }
  }

  char strCmd[lenCmd] = "";
  strcat(strcat(strcat(strCmd, command), paramBuffer), end_token);

  serial_->PutString(strCmd);
  return WaitResponse();
}

EXIT ESP8266::SendCommand(const char *command){
  char strCmd[strlen(command) + 1] = "";
  strcat(strcat(strCmd, command), end_token);

  serial_->PutString(strCmd);
  return WaitResponse();
}

EXIT ESP8266::WaitResponse(WAIT wait_for){
  const int klast_x_chars = 4;
  hwlib::string<klast_x_chars> c = "xxxx";
  
  while (true){
    char z = serial_->GetChar();
    hwlib::cout << z;

    // "shift" index 0 out, put new char on index 3
    for (unsigned int i = 0; i < klast_x_chars; i++){
      c[i] = c[i + 1];
    }
    c[klast_x_chars - 1] = z;

    if(!wait_for){
      if(c == "OK\r\n"){ return EXIT::SUCCES; }
      if(c == "OR\r\n" || c == "IL\r\n"){ return EXIT::FAILURE; }
    } else {
      switch(wait_for){
        case WAIT::RECV:  if(c == "+IPD"){ return EXIT::SUCCES; };break;
        case WAIT::OK:    if(c == "OK\r\n"){ return EXIT::SUCCES; }; break;
        case WAIT::ERROR: if(c == "OR\r\n"){ return EXIT::FAILURE; }; break;
        case WAIT::FAIL:  if(c == "IL\r\n"){ return EXIT::FAILURE; }; break;
        case WAIT::CLOSED:if(c == "ED\r\n"){return EXIT::SUCCES;} break;
        case WAIT::ANY: break;
      }
    }
  }
  return EXIT::NOEXIT;
}