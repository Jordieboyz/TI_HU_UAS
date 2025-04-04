#ifndef TEAM4OVERDRACHT_SRC_ESP8266DRIVER_RESOURCES_H_
#define TEAM4OVERDRACHT_SRC_ESP8266DRIVER_RESOURCES_H_

#define end_token "\r\n"
#define _AT "AT"
#define dec 10

constexpr const char *cmdmap[23] = {_AT,
                                    _AT "+RST",
                                    _AT "E0",
                                    _AT "E1",
                                    _AT "+RESTORE",
                                    _AT "+RFPOWER",
                                    _AT "+CWMODE",
                                    _AT "+CWJAP",
                                    _AT "+CWLAP",
                                    _AT "+CWQAP",
                                    _AT "+CWSAP",
                                    _AT "+CWLIF",
                                    _AT "+CWQIF",
                                    _AT "+CIPSTATUS",
                                    _AT "+CIPSTART",
                                    _AT "+CIPSEND",
                                    _AT "+CIPCLOSE",
                                    _AT "+CIFSR",
                                    _AT "+CIPMUX",
                                    _AT "+CIPSERVER",
                                    _AT "+CIPMODE",
                                    _AT "+CIPAP",
                                    _AT "+PING"};

struct return_data_s {
  void * data;
  int size;
};

enum WAIT : int
{
  ANY,
  OK,
  ERROR,
  CLOSED,
  FAIL,
  RECV
};

enum EXIT : int
{
  FAILURE = -1,
  NOEXIT,
  SUCCES
};

struct params
{
  const char *str;
  bool strCheck;
};

struct ap_conf
{
  const char *ssid;
  const char *pwd;
  int channel;
  int ecn;
  int maxconn;
  bool ssid_hidden;
};

struct ap_conct
{
  const char *ssid;
  const char *pwd;
  const char *bssid;
  int chl;
  int pci_en = 0;
  int reconn_interval = 1;
};

struct send_conf
{
  const char *msg;
  int len;
  int ch = 0;
};



#endif // TEAM4OVERDRACHT_SRC_ESP8266-DRIVER_RESOURCES_H_