#include "stm32f4xx.h"
#include "led.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_flash.h"
#include "usart.h"
#include "beep.h"
#include "key.h"

//void FLASH_ReadOutProtection_Enable(void);

void DelayByDiv(void);
void LedBlink(void);
void BeepAlarm( void );
void KeyTest( void );


int main(int argc, char *argv[])

{
	LED_Init();
	BEEP_Init();
	KEY_Init();      
	GPIO_ResetBits(GPIOF,GPIO_Pin_9);



 
	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	//delay_init(168);	
	uart_init(115200);	
	
	while(1)
	{

#if 1
	u8 t;
	u8 len;	
	u16 times=0; 
		if(USART_RX_STA&0x8000)
		{					   
			len=USART_RX_STA&0x3fff;//µÃµœŽËŽÎœÓÊÕµœµÄÊýŸÝ³€¶È
//			printf("\r\nÄú·¢ËÍµÄÏûÏ¢Îª:\r\n");
			for(t=0;t<len;t++)
			{
				USART_SendData(USART1, USART_RX_BUF[t]);         //ÏòŽ®¿Ú1·¢ËÍÊýŸÝ
				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//µÈŽý·¢ËÍœáÊø
			}
			//		printf("\r\n\r\n");//²åÈë»»ÐÐ
			USART_RX_STA=0;
		}else
		{
			times++;
			if(times%5000==0)
			{
				//printf("\r\nALIENTEK ÌœË÷ÕßSTM32F407¿ª·¢°å Ž®¿ÚÊµÑé\r\n");
				//printf("ÕýµãÔ­×Ó@ALIENTEK\r\n\r\n\r\n");
			}
			if(times%200==0)
				//printf("ÇëÊäÈëÊýŸÝ,ÒÔ»Ø³µŒüœáÊø\r\n");
				GPIO_SetBits(GPIOF,GPIO_Pin_10);
			if(times%30==0)
				GPIO_ResetBits(GPIOF,GPIO_Pin_10);
//				LED0=!LED0;//ÉÁËžLED,ÌáÊŸÏµÍ³ÕýÔÚÔËÐÐ.
			//delay_ms(10);
			DelayByDiv();
		}
#endif		
//KeyTest();
		LedBlink();
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

void LedBlink(void)
{
	GPIO_ResetBits(GPIOF,GPIO_Pin_9);  
	//GPIO_SetBits(GPIOF,GPIO_Pin_10);
	DelayByDiv(); 
	GPIO_SetBits(GPIOF,GPIO_Pin_9);	
	//GPIO_ResetBits(GPIOF,GPIO_Pin_10);
	DelayByDiv(); 
	DelayByDiv();
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
	
