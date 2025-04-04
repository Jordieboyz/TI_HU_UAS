#include "UART/UART.h"
#include "esp8266-driver/esp8266.h"
#include "hwlib.hpp"
#include "ringbuff.h"

#define SUCCES 0
#define FAILURE 1

#define SERVER 1
#define CLIENT 0

class interface {
public:
  /// only add public features in the superclass so both teams can support them.
  interface() {}
  virtual int send(void *data, unsigned int size) = 0;
  virtual return_data_s receive() = 0;
};

class interface_team4 : public interface
{
private:
  /// private vars
  char arr[2048];
  HW_UART serial;
  ESP8266 esp;

  const char *SSID_ = "R2D2-RC-CAR-BEST";
  const char *password_ = "VERY_SECRET_KEY";

  void StartServer()
  {
    esp.InitEspSoftAccessPoint(SSID_, password_);
  }

  void StartClient()
  {
    esp.InitEspClient(SSID_, password_);
    esp.StartTCPconnection("8.8.8.8", 80);
  }

public:
  /// only add public features in the superclass so both teams can support them.
  interface_team4(bool server_mode) : serial(), esp(&serial)
  {
    RingBuffInit(&USART0_rx_buf, 2048, sizeof(char), arr);
    serial.ConfigureInterrupt(&USART0_rx_buf);
    // esp.SetBaudrate();
    if (server_mode)
    {
      StartServer();
    }
    else
    {
      StartClient();
    }
  }

  int send(void *data, unsigned int size) override
  {
    return esp.SendVoid(data, size);
  }

  return_data_s receive() override
  {
    return *esp.ReceiveVoid();
  }

  ~interface_team4() {}
};
