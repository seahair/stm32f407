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
//
#include "stm32f4xx_gpio.h"

#include "stm32f4xx_flash.h"

//void FLASH_ReadOutProtection_Enable(void);

void DelayByDiv(void);

int main(int argc, char *argv[])

{

	LED_Init();
	
	while(1)

	{

	GPIO_ResetBits(GPIOF,GPIO_Pin_9);  //LED0¶ÔÓŠÒýœÅGPIOF.9À­µÍ£¬ÁÁ  µÈÍ¬LED0=0;

	GPIO_SetBits(GPIOF,GPIO_Pin_10);   //LED1¶ÔÓŠÒýœÅGPIOF.10À­žß£¬Ãð µÈÍ¬LED1=1;

	DelayByDiv(); // delay --> not much compiler optimizer settings dependent

	GPIO_SetBits(GPIOF,GPIO_Pin_9);	   //LED0¶ÔÓŠÒýœÅGPIOF.0À­žß£¬Ãð  µÈÍ¬LED0=1;

	GPIO_ResetBits(GPIOF,GPIO_Pin_10); //LED1¶ÔÓŠÒýœÅGPIOF.10À­µÍ£¬ÁÁ µÈÍ¬LED1=0;

	DelayByDiv(); // delay --> not much compiler optimizer settings dependent
	DelayByDiv();
//	printf ("hello world\n");

	}

}


void DelayByDiv(void)

// delay implemented by floating division

// not much compiler optimizer settings dependent

{

	float x=50.0f;

	while (x > 0.0001f)

		x = x/1.0001f; // delay loop

}
