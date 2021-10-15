#include "gpio.h"
#include "defs.h"

#include "tm4c123gh6pm.h"
#include <stdint.h>


extern int buttonFlag;


void PortA_init()
{
    SYSCTL_RCGCGPIO_R |= (1 << 0);
    while ((SYSCTL_RCGCGPIO_R & (1 << 0)) == 0) {}
    GPIO_PORTA_LOCK_R = 0x4C4F434B;
    GPIO_PORTA_CR_R =  (LIGHTS | PED_LIGHTS);
    GPIO_PORTA_DIR_R = (LIGHTS | PED_LIGHTS);
    GPIO_PORTA_DEN_R = (LIGHTS | PED_LIGHTS);
}


void PortB_init()
{
    SYSCTL_RCGCGPIO_R |= (1 << 1);
    while ((SYSCTL_RCGCGPIO_R & (1 << 1)) == 0) {}
    GPIO_PORTB_LOCK_R = 0x4C4F434B;
    GPIO_PORTB_CR_R =  (LIGHTS | PED_LIGHTS);
    GPIO_PORTB_DIR_R = (LIGHTS | PED_LIGHTS);
    GPIO_PORTB_DEN_R = (LIGHTS | PED_LIGHTS);
}


void
PortF_init(){
  SYSCTL_RCGCGPIO_R |= (1<<5);
  while ((SYSCTL_RCGCGPIO_R & (1 << 5)) == 0) {}
  GPIO_PORTF_LOCK_R = 0x4C4F434B;
  GPIO_PORTF_CR_R = T1_SWITCH | T2_SWITCH;
  GPIO_PORTF_DIR_R = 0x0;
  GPIO_PORTF_PUR_R = T1_SWITCH | T2_SWITCH;
  GPIO_PORTF_DEN_R = T1_SWITCH | T2_SWITCH;
  GPIO_PORTF_IM_R =  T1_SWITCH | T2_SWITCH;     // Enabling interrupts for pin 0 and 4
  NVIC_EN0_R |= (1 << 30);                      // Enabling interrupts from Port F
}



void
PortFIntHandler(void){
  if((GPIO_PORTF_MIS_R & T1_SWITCH) != 0){
    buttonFlag = 1;
    GPIO_PORTF_ICR_R |= T1_SWITCH;
  }
  else if((GPIO_PORTF_MIS_R & T2_SWITCH) != 0){
    buttonFlag = 2;
    GPIO_PORTF_ICR_R |= T2_SWITCH;
  }
}
