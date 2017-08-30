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
#include "pwm.h"
#include "capture.h"
#include <stdio.h>
#include <stdlib.h>

void HardInit( void );

int main(int argc, char *argv[])
{
	HardInit();

	while(1)
	{
		delay_ms(10);

		PwmTest();
		//PwmTestDuty();
		//KeyTest();
	    //LedBlink( LedRed );
		
		//printf ("hello world\r\n");
		//BeepAlarm( 500 );

		//printf("HIGH:%lld us\r\n", Time5CalcCaptureTime() );//打印总的高点平时间

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
//	EXTIX_Init();
//	TIM3_Int_Init(5000-1,8400-1);
//	Tim3Init_ms( 1000 );
	TIM14_PWM_Init(500-1,84-1);
//	Time4PwmInit_HZ( 2000 );
//	TIM5_CH1_Cap_Init(0XFFFFFFFF,84-1);
}


