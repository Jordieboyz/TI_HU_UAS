#include "UART.h"
#include "../../hwlib/library/core/hwlib-wait.hpp"

#define NUM_TRIES_NON_BLOCKING 1024

RingBuff USART0_rx_buf;

/* Implicitly reads Receive holding register clearing interrupt. */
extern "C" void USART0_ISR(void)
{
  RingBuffWrite(&USART0_rx_buf, 1, (uint8_t *)&USART0->US_RHR);
}

HW_UART::HW_UART()
{

  // enable the clock to port A
  PMC->PMC_PCER0 = 1 << ID_PIOA;

  //TX1
  PIOA->PIO_PDR |= PIO_PA11;
  PIOA->PIO_ABSR &= ~PIO_PA11;

  //RX1
  PIOA->PIO_PDR |= PIO_PA10;
  PIOA->PIO_ABSR &= ~PIO_PA10;

  // enable the clock to the UART
  PMC->PMC_PCER0 = (0x01 << ID_USART0);

  // Reset and disable receiver and transmitter.
  hw_usart_->US_CR = US_CR_RSTRX | US_CR_RSTTX | US_CR_RXDIS | US_CR_TXDIS;

  // Set the baudrate to 115200.
  hw_usart_->US_BRGR = 45;

  // No parity, normal channel mode.
  hw_usart_->US_MR = US_MR_CHRL_8_BIT | US_MR_PAR_NO;

  // Disable all interrupts.
  hw_usart_->US_IDR = 0xFFFFFFFF;

  // Enable the receiver and the trasmitter.
  hw_usart_->US_CR = US_CR_RXEN | US_CR_TXEN;
};

char HW_UART::GetChar()
{
  char retval;

  if (buffer_ != nullptr)
  {
    while (RingBuffRead(buffer_, 1, &retval) == 0)
      continue;
  }
  else
  {
    while ((hw_usart_->US_CSR & US_CSR_RXRDY) == 0)
    {
    };
    retval = hw_usart_->US_RHR;
  }

  return retval;
}

void HW_UART::PutChar(char c){
  while ((hw_usart_->US_CSR & US_CSR_TXRDY) == 0) {};
  hw_usart_->US_THR = c;
}

void HW_UART::PutString(const char *c)
{
  while (*c != 0)
  {
    // while ((hw_usart_->US_CSR & US_CSR_TXRDY) == 0) {};
    // hw_usart_->US_THR = *c++;
    PutChar(*c++);
  }
};

void HW_UART::ConfigureInterrupt(struct RingBuff *buffer)
{
  buffer_ = buffer;

  NVIC_EnableIRQ(USART0_IRQn);
  NVIC_SetPriority(USART0_IRQn, 1);
  hw_usart_->US_IER |= US_IER_RXRDY;
}

bool HW_UART::GetCharNonBlocking(char *buffer)
{
  for (unsigned i = NUM_TRIES_NON_BLOCKING; i > 0; i--)
  {
    if (buffer_ != nullptr)
    {
      if (RingBuffRead(buffer_, 1, buffer) != 0)
        return true;
    }
    else
    {
      if ((hw_usart_->US_CSR & US_CSR_RXRDY) != 0)
      {
        *buffer = (hw_usart_->US_RHR & 0xFF);
        return true;
      }
    }
  }

  return false;
}

void HW_UART::PutInt(int8_t i)
{
  while ((hw_usart_->US_CSR & US_CSR_TXRDY) == 0)
  {
  };
  hw_usart_->US_THR = i;
}

int8_t HW_UART::GetInt()
{
  int8_t retval;

  if (buffer_ != nullptr)
  {
    while (RingBuffRead(buffer_, 1, &retval) == 0)
      continue;
  }
  else
  {
    while ((hw_usart_->US_CSR & US_CSR_RXRDY) == 0)
    {
    };
    retval = hw_usart_->US_RHR;
  }

  return retval;
}
