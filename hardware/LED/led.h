#ifndef  __LED_H
#define  __LED_H

#include "stm32f4xx.h"

void LED_Init( void );

#if 1
#define LedRed    GPIO_Pin_9
#define LedGreen  GPIO_Pin_10

/*
struct LED{
	u16 pin;
	void (*LedInit) ( u16 pin);
	void (*LedON) ( void );
	void (*LedOFF) ( void );
	void (*LedBlink) ( void );
    u8   (*GetLedStatus) ( void );
	
};*/
	
void LedInit( u16 pin );
void LedON( u16 pin );
void LedOFF( u16 pin );
void LedBlink( u16 pin );
u8   GetLedStatus( u16 pin );
#endif

#endif
