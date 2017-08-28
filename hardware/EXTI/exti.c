#include "exti.h"
#include "delay.h" 
#include "led.h" 
#include "key.h"
#include "beep.h"
#include "stm32f4xx_exti.h"
#include "misc.h"
#include "stm32f4xx_rcc.h"
#include "usart.h"

void EXTI0_IRQHandler(void)
{
	delay_ms(10);	//Ïû¶¶
	if(GetKEYWKUPStatus() == KEY_WK_UP_PRESS)	 
	{
		if( GetLedStatus( LedGreen ) == LedStatus_OFF )
			LedON( LedGreen );
		else
			LedOFF( LedGreen );
		printf ("WK_UP  PRESS\r\n");
		delay_ms(1000);	//Ïû¶¶
	}
	
	EXTI_ClearITPendingBit(EXTI_Line0); //Çå³ýLINE0ÉÏµÄÖÐ¶Ï±êÖ¾Î» 
}	

void EXTI2_IRQHandler(void)
{
	delay_ms(50);	//Ïû¶¶
	if(GetKEY2Status() == KEY2_PRESS)	 
	{
		if( GetLedStatus( LedGreen ) == LedStatus_OFF )
			LedON( LedGreen );
		else
			LedOFF( LedGreen );
		printf ("KEY2  PRESS\r\n");
		delay_ms(1000);	//Ïû¶¶
	}
	
	EXTI_ClearITPendingBit(EXTI_Line2);//Çå³ýLINE2ÉÏµÄÖÐ¶Ï±êÖŸÎ» 
}

void EXTIX_Init(void)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
	
	KEY_Init(); 
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);	
 
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_KEY2);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_KEY1);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_KEY0);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_WK_UP);
	
	/* ÅäÖÃEXTI_Line0 */
	EXTI_InitStructure.EXTI_Line = EXTI_WK_UP;//LINE0
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//ÖÐ¶ÏÊÂ¼þ
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //ÉÏÉýÑØ´¥·¢ 
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;//Ê¹ÄÜLINE0
	EXTI_Init(&EXTI_InitStructure);//ÅäÖÃ
	
	/* ÅäÖÃEXTI_Line2,3,4 */
	EXTI_InitStructure.EXTI_Line = EXTI_KEY0 | EXTI_KEY1 | EXTI_KEY2;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//ÖÐ¶ÏÊÂ¼þ
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //ÏÂ½µÑØ´¥·¢
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;//ÖÐ¶ÏÏßÊ¹ÄÜ
	EXTI_Init(&EXTI_InitStructure);//ÅäÖÃ
 
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;//Íâ²¿ÖÐ¶Ï0
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//×ÓÓÅÏÈ¼¶2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//Ê¹ÄÜÍâ²¿ÖÐ¶ÏÍ¨µÀ
	NVIC_Init(&NVIC_InitStructure);//ÅäÖÃ
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;//Íâ²¿ÖÐ¶Ï2
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//×ÓÓÅÏÈ¼¶2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//Ê¹ÄÜÍâ²¿ÖÐ¶ÏÍ¨µÀ
	NVIC_Init(&NVIC_InitStructure);//ÅäÖÃ
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;//Íâ²¿ÖÐ¶Ï3
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//×ÓÓÅÏÈ¼¶2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//Ê¹ÄÜÍâ²¿ÖÐ¶ÏÍ¨µÀ
	NVIC_Init(&NVIC_InitStructure);//ÅäÖÃ
	
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;//Íâ²¿ÖÐ¶Ï4
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//×ÓÓÅÏÈ¼¶2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//Ê¹ÄÜÍâ²¿ÖÐ¶ÏÍ¨µÀ
	NVIC_Init(&NVIC_InitStructure);//ÅäÖÃ
	   
}












