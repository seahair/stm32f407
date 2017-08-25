#ifndef  __LED_H
#define  __LED_H

void LED_Init( void );

#if 0
#define LedRed    GPIO_Pin_9
#define LedGreen  GPIO_Pin_10

struct LED{
};
	
void LedInit( u32 name );
void LedON( void );
void LedOFF( void );
void LedBlink( void );
bool GetLedStatus( void );
#endif

#endif
