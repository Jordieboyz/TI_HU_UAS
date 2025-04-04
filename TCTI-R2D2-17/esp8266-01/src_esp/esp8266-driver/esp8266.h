#ifndef TEAM4OVERDRACHT_SRC_ESP8266DRIVER_ESP8266_H_
#define TEAM4OVERDRACHT_SRC_ESP8266DRIVER_ESP8266_H_

/// @file

#include <cstring>

#include "../UART/UART.h"
#include "resources.h"


class ESP8266 {
 public:
  ESP8266(HW_UART *_serial_);

  /**
   * Initialize Esp8266-01.
   */  
  void Init();

  /**
   * Basic AT-command to check whether the esp8266-01 is broken or not.
   */ 
  EXIT CheckStarted();

  /**
   * Basic AT-command to reset the esp8266-01
   */ 
  EXIT Reset();

  /**
   * Basic AT-command to disconnect from all AP's
   */ 
  EXIT DisconnectFromAP();

  /**
   * Basic AT-command to factory-reset the esp8266-01
   */ 
  EXIT FactoryReset();

  /**
   * Basic AT-command to show the available AP's
   */ 
  EXIT ShowAvailableAPs();
  
  /**
   * Basic AT-command to get IP from all connnected clients
  **/ 
  EXIT GetConnectedIPs();

  /**
   * Basic AT-command to disconnect all Clients
   */ 
  EXIT DisconnectClients();

  /**
   * Basic AT-command to get the conenction status
   */ 
  EXIT GetConnectionStatus();

  /**
   * Basic AT-command to close the (already opened) connection
   */ 
  EXIT CloseConnection();

    /**
   * Basic AT-command to get the IP-address of the esp8266-01
   */ 
  EXIT GetLocalIP();

  /**
   * Send arbitary data with esp8266-01 via void*
   * @param data              The data to be sent
   * @param size              Corresponding to the legnth of @param data
   */
  EXIT SendVoid(void *data, int size);

  /**
   * Receive and save incoming data
   */
  return_data_s *ReceiveVoid();

  /**
   * Initialize the esp8266-01 as an Station
   * @param ssid              Name of the AP
   * @param pwd               Password to connect to an AP
   */
  EXIT InitEspClient(const char *ssid, const char *pwd);

  /**
   * Initialize the esp8266-01 as an Access Point
   * @param ssid              Name of the AP
   * @param pwd               Password has to be in length [8-63]
   * @param port              Port number
   */
  EXIT InitEspSoftAccessPoint(const char *ssid, const char *pwd, int port = 333);

  /**
   * Set the type of transmission
   * @param mode              0: normal transmission, 1: wifi transmission
   */
  EXIT SetTransmissionMode(bool mode);

  /**
   * Change the ip adress of the esp8266-01
   * @param ip                New IP adress
   * @param gateway           New gateway
   * @param netmask           New netmask based on @param ip
   */
  EXIT SetLocalIp(const char *ip, const char *gateway = "",
                  const char *netmask = "");

  /**
   * Send an AT-command to the esp8266-01
   * @param mode              0: close server, 1: create server
   * @param port              Port number
   */
  EXIT CreateServer(bool mode, int port = 333);

  /**
   * Send an AT-command to the esp8266-01
   * @param power             Power to set the RF ann TX Power, range [40~82]
   */
  EXIT SetWifiPower(int power);

  /**
   * Manage esp's echo (of AT-commands)
   * @param mode              0: turn echo off, 1: turn echo on
   */
  EXIT EnableEcho(bool mode);

  /**
   * Configure the esp as an AccesPoint (AP)
   * @param ssid              Visible name for AP (max 31 char)
   * @param pwd               For @param ecn = 0, pwd could be set to NULL,
   * otherwise chars have to be in length [8-63]
   * @param chl               WiFi channel number, range [1-20]
   * @param max_conn          Max possible connections to the AP, range [1-10]
   * @param ecn               Encryption, 0: OPEN(default), 3: WPA2_PSK
   * @param ssid_hidden       enable of discable broadcating the SSID
   */
  EXIT ConfigureAP(const char *ssid, const char *pwd, int chl = 0, int ecn = 0,
                   int maxconn = 1, bool ssid_hidden = 0);

  /**
   * Configure an TCP connection
   * @param remote_host
   * @param port
   */
  EXIT StartTCPconnection(const char *remote_host, int port = 333);

  /**
   * Enable multiple connections
   * @param multiconn         enable or diable multiple connections
   */
  EXIT EnableMultipleConnections(bool multiconn);

  /**
   * Set esp8266-01 in specific wifi-mode
   * @param mode              0: wifi disabled, 1: Access Point, 2: station, 3:
   * both(2 and 3)
   * @param autoconn          enable of disable automatic connecion
   */
  EXIT SetWifiMode(int mode, bool autoconn = 1);

  /**
   * Connect to an Access Point (AP)
   * @param ssid
   * @param pwd
   * @param bssid
   */
  EXIT ConnectToAP(const char *ssid, const char *pwd, const char *bssid = "");

  /**
   * Ping a remote_host
   * @param remote_host
   */
  EXIT Ping(const char *remote_host);

private:

  /**
   * Send an AT-command to the esp8266-01
   * @param command           A command corresponding with an enum value in @enum cmd
   * @param p                 A pointer to a @struct params or a list in for * params
   * @param n                 The amount of @struct params in @param p
   */
  EXIT SendCommand(const char *command, params *p, unsigned int n = 1);

  /**
   * Send an AT-command to the esp8266-01
   * @param command           A command corresponding with an enum value in @enum cmd
   */
  EXIT SendCommand(const char *command);

  /**
   * Wait for the right response.
   * @param wait_for          A int corresponding with any kind of return message wether this is an error or succes
   */
  EXIT WaitResponse(WAIT wait_for = WAIT::ANY);

  int8_t ints[1048];
  HW_UART *serial_;
  return_data_s rvoid_;

  char buff_[4];
  char buff2_[4];

  // has to be in range [0~4] in our case we just need 1 connection. this means
  // also just 1 channel.
  const int kCh = 1;

  enum cmd
  {
    AT,
    RST,
    ATE0,
    ATE1,
    RESTORE,
    RFPOWER,
    CWMODE,
    CWJAP,
    CWLAP,
    CWQAP,
    CWSAP,
    CWLIF,
    CWQIF,
    CIPSTATUS,
    CIPSTART,
    CIPSEND,
    CIPCLOSE,
    CIFSR,
    CIPMUX,
    CIPSERVER,
    CIPMODE,
    CIPAP,
    PING
  };
};

#endif // TEAM4OVERDRACHT_SRC_ESP8266-DRIVER_ESP8266_H_