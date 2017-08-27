#include "beep.h" 
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "delay.h"

void BEEP_Init(void)
{   
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);//ʹ��GPIOFʱ��
  
  //��ʼ����������Ӧ����GPIOF8
  GPIO_InitStructure.GPIO_Pin = BEEPPIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//����
  GPIO_Init(GPIOF, &GPIO_InitStructure);//��ʼ��GPIO
	
  GPIO_ResetBits(GPIOF, BEEPPIN );  //��������Ӧ����GPIOF8���ͣ� 
}

void BeepON( void )
{
	GPIO_SetBits(GPIOF, BEEPPIN );  
}

void BeepOFF( void )
{
	GPIO_ResetBits(GPIOF, BEEPPIN );
}

void BeepAlarm( u16 hz )
{
	u32 t=0;
	for(t=0; t<655; t++)
	{
		BeepON( );
		delay_ms( 500/hz );
		BeepOFF( );
		delay_ms( 500/hz );
	}
}




