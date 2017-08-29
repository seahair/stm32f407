#ifndef  __PWM_H__
#define  __PWM_H__

#include "sys.h"


#define  PWNCYCLE  500


void TIM14_PWM_Init(u32 arr,u32 psc);
void Time4PwmInit_HZ( u16 hz );
void Time4PwnSetDuty( u16 duty );
void Time4PwmDutyIncrease( u16 step );
void Time4PwmDutyDecrease( u16 step );

#endif
