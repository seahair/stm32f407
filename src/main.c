#include "stm32f4xx.h"
#include "led.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_flash.h"
#include "usart.h"
#include "beep.h"
#include "key.h"
#include "delay.h"
#include "exti.h"
#include "time.h"
#include <stdio.h>
#include <stdlib.h>

void HardInit( void );

int main(int argc, char *argv[])
{
	HardInit();

	//u8 test[] = {'h', 'e', 'l', 'l', 'o', '\r','\n'};
	while(1)
	{
		//	u8 t;
		//for(t=0;t<7;t++)
		//{
		//	USART_SendData(USART1, test[t]);
		//	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
		//}
		
//		KeyTest();
		LedBlink( LedRed );
		
		printf ("hello world\r\n");
		//BeepAlarm( 500 );

	}
}

	
void HardInit( void )
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init( 168 );
	LedInit( LedRed );
	LedInit( LedGreen );	
	BEEP_Init();
	uart_init(115200);
	KEY_Init();
	EXTIX_Init();
	TIM3_Int_Init(5000-1,8400-1);
	//Tim3Init_ms( 1000 );
}

