/************************************************************************************************************

 * Test-program for Olimex “STM32-H103”, header board for “STM32F103RBT6”.

 * After program start green LED (STAT) will blink, when jumper LED_E is closed.

 *

 * Running Release code will set ReadOutProtection (see down) via function FLASH_ReadOutProtection_Enable().

 * Do not run Release code until you know how to set back ReadOutProtection!

 ************************************************************************************************************/

#include "stm32f4xx.h"
#include "led.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_flash.h"
//#include "usart.h"
#include "beep.h"

//void FLASH_ReadOutProtection_Enable(void);

void DelayByDiv(void);
void LedBlink(void);

int main(int argc, char *argv[])

{
	LED_Init();
	BEEP_Init();
	while(1)
	{
		
		//LedBlink();
		//printf ("hello world\n");
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
	GPIO_SetBits(GPIOF,GPIO_Pin_10);
	DelayByDiv(); 
	GPIO_SetBits(GPIOF,GPIO_Pin_9);	
	GPIO_ResetBits(GPIOF,GPIO_Pin_10);
	DelayByDiv(); 
	DelayByDiv();
}
