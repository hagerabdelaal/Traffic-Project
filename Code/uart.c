#include <stdint.h>

#include "uart.h"
#include "tm4c123gh6pm.h"

void
UART0_init(void){
  // Enabling clock to UART 0
  SYSCTL_RCGCUART_R |= 0x01;
  
  // Enabling alterantive functions for port A
  GPIO_PORTA_AFSEL_R |= 0x3; 
  GPIO_PORTA_PCTL_R |= 0x11;
  GPIO_PORTA_DEN_R |= 0x3;
  
  // Configuring the UART registers
  UART0_CTL_R &= ~0x1;          // Disable
  UART0_IBRD_R = 104;           // Integer portion of the divisor
  UART0_FBRD_R = 11;            // Fractional portion of the divisor
  UART0_LCRH_R = 0x70;          // Enabling FIFO and setting word length to 8
  UART0_CC_R = 0x0;             // Setting the clock source
  UART0_CTL_R |= 0x101;         // Enabling Tx
}


void
UART0_transmit(char* msg){
 while(*msg != 0){
    while((UART0_FR_R & 0x20) != 0);
    UART0_DR_R = *msg;
    msg++;
  }
}