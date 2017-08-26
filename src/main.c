#include "stm32f4xx.h"
#include "led.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_flash.h"
#include "usart.h"
#include "beep.h"
#include "key.h"

void DelayByDiv(void);
//void LedBlink(void);
void BeepAlarm( void );
void KeyTest( void );

void HardInit( void );


int main(int argc, char *argv[])

{
	HardInit();

	BEEP_Init();
	KEY_Init();      
	GPIO_ResetBits(GPIOF,GPIO_Pin_9);
 


	uart_init(115200);	
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

		
		
#if 0
	u8 t;
	u8 len;	
	u16 times=0; 
		if(USART_RX_STA&0x8000)
		{					   
			len=USART_RX_STA&0x3fff;
			for(t=0;t<len;t++)
			{
				USART_SendData(USART1, USART_RX_BUF[t]);
				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
			}

			USART_RX_STA=0;
		}else
		{
			times++;
			if(times%5000==0)
			{


			}
			if(times%200==0)

				GPIO_SetBits(GPIOF,GPIO_Pin_10);
			if(times%30==0)
				GPIO_ResetBits(GPIOF,GPIO_Pin_10);

			DelayByDiv();
		}
#endif
		
		//KeyTest();
		LedBlink( LedRed );
		LedBlink( LedGreen );
		//printf ("hello world\n");
		//BeepAlarm();
	}
}

void DelayByDiv(void)
{
	float x=50.0f;
	while (x > 0.0001f)
		x = x/1.0001f; // delay loop
}

void BeepAlarm( void )
{
	GPIO_ResetBits(GPIOF,GPIO_Pin_8); //BEEP no-alarm when this pin low
	DelayByDiv();
	GPIO_SetBits(GPIOF,GPIO_Pin_8);   //BEEP Alarm when this pin hight
	DelayByDiv();
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
		}else  DelayByDiv();
}
	
void HardInit( void )
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	LedInit( LedRed );
	LedInit( LedGreen );	
}
