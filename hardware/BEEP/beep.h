#ifndef __BEEP_H
#define __BEEP_H	 
#include "sys.h" 

//#define BEEP PFout(8)	// ·äÃùÆ÷¿ØÖÆIO 
#define BEEPPIN  GPIO_Pin_8
void BEEP_Init(void);
void BeepON( void );
void BeepOFF( void );
void BeepAlarm( u16 hz );


#endif

















