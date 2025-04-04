#ifndef _UART_INTERFACE_HPP
#define _UART_INTERFACE_HPP

class UART_Interface {

public:

    virtual char GetChar(void) = 0;
    
    virtual void PutChar(char c) = 0;

    virtual void PutString(const char * c) = 0;
    
};


#endif //_USART_INTERFACE_HPP