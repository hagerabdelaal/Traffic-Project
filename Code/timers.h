#ifndef __TIMER_H__
#define __TIMER_H__

void Timer0_init(void);
void Timer1_init(void);

void Timer0AIntHandler(void);
void Timer1AIntHandler(void);
#endif