#ifndef __DEFS_H__
#define __DEFS_H__

#define TRAFFIC1 GPIO_PORTA_DATA_BITS_R  
#define TRAFFIC2 GPIO_PORTB_DATA_BITS_R  

#define LED_RED     (1U << 2)
#define LED_YELLOW  (1U << 3) 
#define LED_GREEN   (1U << 4)
#define LIGHTS (LED_RED | LED_YELLOW | LED_GREEN)

#define PED_RED   (1 << 5)
#define PED_GREEN (1 << 6)
#define PED_LIGHTS (PED_GREEN | PED_RED)

#define T1_SWITCH (1 << 0)
#define T2_SWITCH (1 << 4)


#define OneSecond 15999999 

#endif