#ifndef  __PWM_H__
#define  __PWM_H__

#include "sys.h"


#define  PWMTIME   TIM14
#define  PWMCYCLE  500


void TIM14_PWM_Init(u32 arr,u32 psc);
void Time14PwmInit_HZ( u32 hz );
void Time14PwnSetDuty( u16 duty );
void Time14PwmDutyIncrease( u16 step );
void Time14PwmDutyDecrease( u16 step );
void PwmTest( void );
void PwmTestDuty( void );

#endif
