#ifndef  __CAPTURE_H__
#define  __CAPTURE_H__

#include "sys.h"


#define  CAPTUREFINISH        0X80
#define  CAPTUREHIGHLEVEL     0X40
#define  CAPTUREFULL          0X3F

void TIM5_CH1_Cap_Init(u32 arr,u16 psc);
u32  Time5CalcCaptureTime( void );

//extern u8 TIM5CH1_CAPTURE_STA;
//extern u32 TIM5CH1_CAPTURE_VAL;

#endif
