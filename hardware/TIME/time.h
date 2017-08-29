#ifndef __TIME_H__
#define __TIME_H__

#include "stm32f4xx_tim.h"

void TIM3_Int_Init(u16 arr,u16 psc);
void Time3Enable( void );
void Time3Disable( void );


#endif
