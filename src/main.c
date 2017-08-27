#include "stm32f4xx.h"
#include "led.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_flash.h"
#include "usart.h"
#include "beep.h"
#include "key.h"
#include "delay.h"



void KeyTest( void );

void HardInit( void );


int main(int argc, char *argv[])

{
	HardInit();
	KEY_Init();      


//	u8 test1[5] = "hello";
	u8 test[] = {'h', 'e', 'l', 'l', 'o', '\r','\n'};
	while(1)
	{
		u8 t;
		for(t=0;t<7;t++)
		{
			USART_SendData(USART1, test[t]);
			while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
		}
		
		//KeyTest();
		LedBlink( LedRed );

		//printf ("hello world\n");
		//BeepAlarm( 500 );

	}
}


void KeyTest( void )
{
   	u8 key;
		key=KEY_Scan(0);		//µÃµœŒüÖµ
	   	if(key)
		{						   
			switch(key)
			{				 
				case WKUP_PRES:	//¿ØÖÆ·äÃùÆ÷
					GPIO_ResetBits(GPIOF,GPIO_Pin_9);
					break;
				case KEY0_PRES:	//¿ØÖÆLED0·­×ª
					GPIO_SetBits(GPIOF,GPIO_Pin_9);
					break;
				case KEY1_PRES:	//¿ØÖÆLED1·­×ª	 
					GPIO_ResetBits(GPIOF,GPIO_Pin_10);
					break;
				case KEY2_PRES:	//Í¬Ê±¿ØÖÆLED0,LED1·­×ª 
					GPIO_SetBits(GPIOF,GPIO_Pin_10);
					break;
			}
		}else
			delay_ms( 100 );
}
	
void HardInit( void )
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init( 168 );
	LedInit( LedRed );
	LedInit( LedGreen );	
	BEEP_Init();
	uart_init(115200);	
}
