#include "time.h"
#include "stm32f4xx_tim.h"
#include "led.h"
#include "stm32f4xx_rcc.h"
#include "misc.h"

void Time3Enable( void )
{
	TIM_Cmd(TIM3, ENABLE);
}

void Time3Disable( void )
{
	TIM_Cmd(TIM3, DISABLE);
}

void TIM3_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  //enable RCC of Time3

	TIM_TimeBaseInitStructure.TIM_Period = arr; 
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; 
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;

	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);   //config Time3

	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);   //Enable Time3 IT

	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; 
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	
}


void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) //溢出中断
	{
		LedRollBack( LedGreen );
	}
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update); //清除中断标志位
}
