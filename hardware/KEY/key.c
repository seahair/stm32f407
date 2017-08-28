#include "key.h"
#include "delay.h" 
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "led.h"


void KEY_Init(void)
{
	
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOE, ENABLE);// GPIOA And GPIOE
 
	GPIO_InitStructure.GPIO_Pin = KEY0|KEY1|KEY2; //KEY0 KEY1 KEY2 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;// Pin load to GND by Key, So Pull UP
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	 
	GPIO_InitStructure.GPIO_Pin = WK_UP;    //KEY WEAKUP
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN ;//Pin load to 3V3 by Key, So Pull DOWN
	GPIO_Init(GPIOA, &GPIO_InitStructure);
 
}

u8 GetKEY0Status( void )
{
	return GPIO_ReadInputDataBit(GPIOE, KEY0);
}

u8 GetKEY1Status( void )
{
	return GPIO_ReadInputDataBit(GPIOE, KEY1);
}

u8 GetKEY2Status( void )
{
	return GPIO_ReadInputDataBit(GPIOE, KEY2);
}

u8 GetKEYWKUPStatus( void )
{
	return GPIO_ReadInputDataBit(GPIOA, WK_UP);
}


u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//°´¼ü°´ËÉ¿ª±êÖ¾
	if(mode)key_up=1;  //Ö§³ÖÁ¬°´		  
	if(key_up &&
	   (GetKEY0Status()    == KEY0_PRESS ||
		GetKEY1Status()    == KEY1_PRESS ||
		GetKEY2Status()    == KEY2_PRESS ||
		GetKEYWKUPStatus() == KEY_WK_UP_PRESS )
	  )
	{
		delay_ms(10);//È¥¶¶¶¯ 
		key_up=0;
		if( GetKEY0Status() == KEY0_PRESS )return KEY0_ACTIVE;
		else if( GetKEY1Status()    == KEY1_PRESS )return KEY1_ACTIVE ;
		else if( GetKEY2Status()    == KEY2_PRESS )return KEY2_ACTIVE;
		else if( GetKEYWKUPStatus() == KEY_WK_UP_PRESS )return WKUP_ACTIVE;
	}else
	if( GetKEY0Status()    == KEY0_RELEASE &&
		GetKEY1Status()    == KEY1_RELEASE &&
		GetKEY2Status()    == KEY2_RELEASE &&
		GetKEYWKUPStatus() == KEY_WK_UP_RELEASE 
		)
		key_up=1; 	    
 	return 0;// ÎÞ°´¼ü°´ÏÂ
}


void KeyTest( void )
{
   	u8 key;
	key=KEY_Scan(0);		//µÃµœŒüÖµ
	if(key)
	{						   
		switch(key)
		{				 
		case WKUP_ACTIVE:	//¿ØÖÆ·äÃùÆ÷
			LedON( LedRed );
			break;
		case KEY0_ACTIVE:	//¿ØÖÆLED0·­×ª
			LedOFF( LedRed );
			break;
		case KEY1_ACTIVE:	//¿ØÖÆLED1·­×ª	 
			LedON( LedGreen );
			break;
		case KEY2_ACTIVE:	//Í¬Ê±¿ØÖÆLED0,LED1·­×ª 
			LedOFF( LedGreen );
			break;
		}
	}else
		delay_ms( 100 );
}




















