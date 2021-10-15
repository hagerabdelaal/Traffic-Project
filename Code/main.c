#include <stdint.h>

#include "tm4c123gh6pm.h"
#include "defs.h"
#include "gpio.h"
#include "timers.h"
#include "uart.h"

enum State{T1_GREEN, T1_YELLOW, T1_WAIT, T2_GREEN, T2_YELLOW, T2_WAIT, T1_PED, T2_PED};

// State Variables
enum State state;
int counter = 0;
int button_lock = 0;

// Flags 
int counterFlag = 0;
int buttonFlag = 0;
int buttonTimerFlag = 0;
int buttonTimerState = 0;

// Flag Hanlders
void counterHandler(void);
void buttonHandler(int);
void buttonTimerHandler(void);

void sendCurrentState(void);

int main()
{  
  // Initializations
   PortA_init();
   PortB_init();
   PortF_init();
   
   Timer0_init();
   Timer1_init();
   
   UART0_init();
   
  // Initial State
  state = T2_WAIT;
  TRAFFIC2[LIGHTS] = LED_RED;
  TRAFFIC2[PED_LIGHTS] = PED_GREEN;
  
  __asm("CPSIE  I");

  while (1)
  { 
    if(counterFlag != 0)
      counterHandler();

    if(buttonFlag != 0)
      buttonHandler(buttonFlag);

    if(buttonTimerFlag != 0)
      buttonTimerHandler(); 
  } 
}


void
counterHandler(void){
    counterFlag = 0;
    counter++;                                    // Incrementing the Counter

  if(state == T1_WAIT && counter == 1){
    TRAFFIC2[LIGHTS]=LED_GREEN;                   // Turn on T2 green led
    TRAFFIC2[PED_LIGHTS] = PED_RED;               // Turning T2 pedestrain red
    state=T2_GREEN;                               // Update el State
    sendCurrentState();                           // Send current state
    counter = 0;                                  // clear counter
  }
  else if(state ==T2_WAIT && counter == 1){
    TRAFFIC1[LIGHTS]= LED_GREEN;                   // Turn on T1 green led
    TRAFFIC1[PED_LIGHTS] = PED_RED;                // Turning T1 pedestrain red
    state=T1_GREEN;                                // Update el state
    sendCurrentState();                            // Send current state
    counter = 0;                                   // clear counter  
  }
  else if(state == T1_GREEN && counter == 5){
     TRAFFIC1[LIGHTS]= LED_YELLOW;                  // Turn-on Yellow led
     state=T1_YELLOW;                               // Update el state
     counter = 0;                                   // clear counter
  }
  else if(state ==T2_GREEN && counter == 5){
    TRAFFIC2[LIGHTS]=LED_YELLOW;                   // Turn on T2 Yellow LED
    state=T2_YELLOW;                               // Update el state
    counter = 0;                                   // clear counter  
  }
  else if(state ==T1_YELLOW && counter == 2){
    TRAFFIC1[LIGHTS]=LED_RED;                    // Turn-on T1 RED led
    TRAFFIC1[PED_LIGHTS] = PED_GREEN;            // Turning T1 pedestrain green
    state=T1_WAIT;                               // Update el state
    counter = 0;                                 // clear counter
  }
  else if(state ==T2_YELLOW && counter == 2){
    TRAFFIC2[LIGHTS]=LED_RED;                   // Turn-on T2 RED led
    TRAFFIC2[PED_LIGHTS] = PED_GREEN;           // Turning T2 pedestrain green
    state=T2_WAIT;                              // Update el state
    counter = 0;                                // clear counter  
  }
}


void
buttonHandler(int button){
  buttonFlag = 0;

  if(button == 1 && state == T1_GREEN && button_lock == 0){
      button_lock = 1;                          // Locking successive use
      state = T1_PED;                           // Updating state
      sendCurrentState();                       // Send current state
      TIMER1_CTL_R = 0x00000003;                // Enabling Timer1
      TIMER0_CTL_R = 0x0;                       // Disabling Timer0
      TRAFFIC1[LIGHTS] = LED_RED;               // Turn the traffic red
      TRAFFIC1[PED_LIGHTS] = PED_GREEN;         // Turn the pedestrian lights green
  }
  else if(button == 2 && state == T2_GREEN && button_lock == 0){
      button_lock = 1;                          // Locking successive use
      state = T2_PED;                           // Updating state
      sendCurrentState();                       // Send current state
      TIMER1_CTL_R = 0x00000003;                // Enabling Timer1
      TIMER0_CTL_R = 0x0;                       // Disabling Timer0
      TRAFFIC2[LIGHTS] = LED_RED;               // Turn the traffic red
      TRAFFIC2[PED_LIGHTS] = PED_GREEN;         // Turn the pedestrian lights green
  }
}


void
buttonTimerHandler(){
  buttonTimerFlag = 0;

   //------- First call to return to original state
   if(buttonTimerState == 0){
    TIMER0_CTL_R = 0x00000003;                  // Enabling Timer0
    
    if(state == T1_PED){
        state = T1_GREEN;                       // Updating state
        sendCurrentState();                     // Send current state
        TRAFFIC1[PED_LIGHTS] = PED_RED;         // Turning pedestrian lights red
        TRAFFIC1[LIGHTS] = LED_GREEN;           // Turning traffic light green
    }
    
    if(state == T2_PED){
        state = T2_GREEN;                       // Updating state
        sendCurrentState();                     //Send current state
        TRAFFIC2[PED_LIGHTS] = PED_RED;         // Turning pedestrian lights red
        TRAFFIC2[LIGHTS] = LED_GREEN;           // Turning traffic light green
    }
      
    // Configuring the timer for the second run
    TIMER1_TAILR_R = OneSecond;
    TIMER1_CTL_R = 0x3;
    buttonTimerState = 1;
  }

  //------- Second call for locking the button
  else if(buttonTimerState == 1){
     button_lock = 0;                           // Unlocking the buttons
     TIMER1_TAILR_R = OneSecond * 2;            // Re-configuring Timer1
     buttonTimerState = 0;
  }
}

void sendCurrentState()
{
  if (state == T1_GREEN)
  {
    UART0_transmit("CARS NORTH SOUTH\n\r\n");
  }
  else if (state == T2_GREEN)
  {
    UART0_transmit("CARS EAST WEST\n\r\n");
  }
  else if (state == T1_PED)
  {
    UART0_transmit("PEDESTRIAN NORTH SOUTH\n\r\n");
  }
  else if (state == T2_PED)
  {
    UART0_transmit("PEDESTRIAN EAST WEST\n\r\n");
  }
}