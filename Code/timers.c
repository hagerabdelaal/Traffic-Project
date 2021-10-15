#include "timers.h"
#include "defs.h"

#include "tm4c123gh6pm.h"
#include <stdint.h>


extern int counterFlag;
extern int buttonTimerFlag;

void Timer0_init()
{
    SYSCTL_RCGCTIMER_R |= (1<<0);             //enable clock to timer
    TIMER0_CTL_R = 0x0;                       //disable timer0A           
    TIMER0_CFG_R = 0x0;                       //32 bit mode    
    TIMER0_TAMR_R = 0x00000002;               //  periodic mode,default down-count settings.            
    TIMER0_TAILR_R = OneSecond ; 
    TIMER0_ICR_R = 0x00000001;                //  clear TIMER0A timeout flag
    TIMER0_IMR_R = 0x00000001;
    NVIC_EN0_R |= (1<<19); 
    TIMER0_CTL_R = 0x00000003;               // enable TIMER0A
}

void
Timer0AIntHandler(void){
   TIMER0_ICR_R = TIMER_ICR_TATOCINT;              // acknowledge timer0A timeout
   counterFlag = 1;                                // Setting the flag
}

void
Timer1_init(void){
    SYSCTL_RCGCTIMER_R |= (1<<1);             // enable clock to timer1
    TIMER1_CTL_R = 0x0;                       // disable timer0A           
    TIMER1_CFG_R = 0x0;                       // 32 bit mode    
    TIMER1_TAMR_R = 0x00000001;               // One-shot down-count 
    TIMER1_TAILR_R = OneSecond * 2;           // Setting period for 2 seconds
    TIMER1_ICR_R = 0x00000001;                // clear TIMER0A timeout flag
    TIMER1_IMR_R = 0x00000001;                // Enabling timeout interrupt     
    NVIC_EN0_R |= (1<<21);                    // Enabling interrupts from Timer1
}

void
Timer1AIntHandler(void){
   TIMER1_ICR_R = TIMER_ICR_TATOCINT;   // Acknoledging interrupt
   buttonTimerFlag = 1;                 // Setting the flag
}