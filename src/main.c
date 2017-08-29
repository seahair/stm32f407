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
#include <stdio.h>
#include <stdlib.h>

void HardInit( void );

int main(int argc, char *argv[])
{
	HardInit();
	u16 led0pwmval=0; 
	u8 dir=1;
	while(1)
	{
		delay_ms(10);
		if(dir)led0pwmval++;//dir==1 led0pwmval 递增
		else led0pwmval--; //dir==0 led0pwmval 递减
		if(led0pwmval>300)dir=0;//led0pwmval 到达 300 后，方向为递减
		if(led0pwmval==0)dir=1; //led0pwmval 递减到 0 后，方向改为递增
		Time4PwnSetDuty( led0pwmval ); //修改比较值，修改占空比

		
//		KeyTest();
	 //	LedBlink( LedRed );
		
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
//	TIM3_Int_Init(5000-1,8400-1);
//	Tim3Init_ms( 1000 );
	TIM14_PWM_Init(500-1,84-1);
}

