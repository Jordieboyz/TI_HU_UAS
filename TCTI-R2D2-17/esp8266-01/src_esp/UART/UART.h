#ifndef UART_H_
#define UART_H_

#include "../ringbuff.h"
#include "UART_Interface.h"


#define register
#include "sam3x8e.h"
#undef register

/** @file **/

extern RingBuff USART0_rx_buf;

class HW_UART : public UART_Interface
{
public:
  /** 
   * @brief
   *  Configures the hardware uart, for now its only available
   *  on the RX1 and TX1 pins.  
   */
  HW_UART();

  /** 
   * @brief
   *  Returns data received on the RX line.
   */
  virtual char GetChar(void) override;

  /** 
   * @brief
   *  Puts a single char on the TX line.
   */
  virtual void PutChar(char c) override;

  /** 
   * @brief
   *  Puts a string on the TX line.
   */
  virtual void PutString(const char *c) override;

  /** 
   * @brief
   *  Sets buffer as RX-buffer and enables interrupts.
   */
  void ConfigureInterrupt(struct RingBuff *buffer);

  /**
   * @brief
   *  Retrieves a char puts it in buff.
   * @retval
   *  Returns true if success, returns false on timeout.
   */
  bool GetCharNonBlocking(char *buff);

  void PutInt(int8_t i);

  /**
   * @brief
   *  Returns data received on the RX line.
   */
  virtual int8_t GetInt(void);

private:
  Usart *hw_usart_ = USART0;
  RingBuff *buffer_ = nullptr;
};

#endif //UART_H_

//TODO: Add support for different USART ports other than just USART0