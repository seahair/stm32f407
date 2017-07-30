/************************************************************************************************************

 * Test-program for Olimex “STM32-H103”, header board for “STM32F103RBT6”.

 * After program start green LED (STAT) will blink, when jumper LED_E is closed.

 *

 * Running Release code will set ReadOutProtection (see down) via function FLASH_ReadOutProtection_Enable().

 * Do not run Release code until you know how to set back ReadOutProtection!

 ************************************************************************************************************/

#include "stm32f4xx.h"

#include "stm32f4xx_rcc.h"

#include "stm32f4xx_gpio.h"

#include "stm32f4xx_flash.h"

void FLASH_ReadOutProtection_Enable(void);

void DelayByDiv(void);

int main(int argc, char *argv[])

{

	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);//Ê¹ÄÜGPIOFÊ±ÖÓ
	


	//GPIOF9,F10³õÊŒ»¯ÉèÖÃ

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;//LED0ºÍLED1¶ÔÓŠIO¿Ú

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//ÆÕÍšÊä³öÄ£Êœ

	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//ÍÆÍìÊä³ö

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz

	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//ÉÏÀ­

	GPIO_Init(GPIOF, &GPIO_InitStructure);//³õÊŒ»¯GPIO

	
	GPIO_SetBits(GPIOF,GPIO_Pin_9 | GPIO_Pin_10);//GPIOF9,F10ÉèÖÃžß£¬µÆÃð


	
//	FLASH_ReadOutProtection_Enable(); // enable ReadOutProtection when running Release code

	while(1)

	{


	GPIO_ResetBits(GPIOF,GPIO_Pin_9);  //LED0¶ÔÓŠÒýœÅGPIOF.9À­µÍ£¬ÁÁ  µÈÍ¬LED0=0;

	GPIO_SetBits(GPIOF,GPIO_Pin_10);   //LED1¶ÔÓŠÒýœÅGPIOF.10À­žß£¬Ãð µÈÍ¬LED1=1;


	DelayByDiv(); // delay --> not much compiler optimizer settings dependent
	

	GPIO_SetBits(GPIOF,GPIO_Pin_9);	   //LED0¶ÔÓŠÒýœÅGPIOF.0À­žß£¬Ãð  µÈÍ¬LED0=1;

	GPIO_ResetBits(GPIOF,GPIO_Pin_10); //LED1¶ÔÓŠÒýœÅGPIOF.10À­µÍ£¬ÁÁ µÈÍ¬LED1=0;


	DelayByDiv(); // delay --> not much compiler optimizer settings dependent
	DelayByDiv();

	}

}

/*void FLASH_ReadOutProtection_Enable(void)

// If FLASH readout protection not already set, enable protection and reset device

//

// NOTES: The user area of the Flash memory can be protected against read by untrusted code.

// Protection is enabled only for firmware compiled with flag RELEASE_PUBLIC set (see makefile).

// When readout protection is set debugging via JTAG is not possible any more.

// If the read protection is set while the debugger is still connected through JTAG/SWD, apply a

// POR (power-on reset) instead of a system reset (without debugger connection).

{

	if (FLASH_GetReadOutProtectionStatus() != SET)

	{

#ifdef RELEASE_PUBLIC // HINT: define is done via makefile

		FLASH_Unlock();

		if (FLASH_ReadOutProtection(ENABLE) != FLASH_COMPLETE) // set readout protection

		{

// ERROR: could not program read protection

		}

		else

			NVIC_SystemReset(); // protection set --> reset device to enable protection

#else

// output warning message

#endif

	}

}
*/
void DelayByDiv(void)

// delay implemented by floating division

// not much compiler optimizer settings dependent

{

	float x=50.0f;

	while (x > 0.0001f)

		x = x/1.0001f; // delay loop

}
