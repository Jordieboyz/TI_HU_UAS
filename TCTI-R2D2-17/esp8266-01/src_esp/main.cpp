#include "interface_team4.hpp"

struct my_info_t
{
  int8_t steer;
  int8_t throttle;
};

int main()
{
  hwlib::wait_ms(1000);
  
  HW_UART serial;
  auto esp = ESP8266(&serial);

  char arr[2048];
  RingBuffInit(&USART0_rx_buf, 2048, sizeof(char), arr);
  serial.ConfigureInterrupt(&USART0_rx_buf);

  const char *SSID_ = "LAPTOP-J2L30KQP";
  const char *password_ = "LAPTOP1234";

  esp.Reset();
  hwlib::wait_ms(1000);
  esp.ConnectToAP(SSID_, password_);
  esp.EnableMultipleConnections(1);
  esp.CreateServer(1, 9999);
  esp.GetLocalIP();

  while(true){
    hwlib::cout << serial.GetChar();
  }
}
