#include "pad.h" 
#include "delay.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"
#include "stdio.h"

#define TPAD_ARR_MAX_VAL	0XFFFFFFFF
u16 PadDefaultValue = 0;
#define PADGATEWALL		100

void PadOutPutInit( void )
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin		= GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType	= GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd	= GPIO_PuPd_DOWN;
	
	GPIO_Init( GPIOA, &GPIO_InitStructure );
}

void PadOutPutDown( void )
{
	GPIO_ResetBits( GPIOA, GPIO_Pin_5 );
}

void PadOutPutUp( void )
{
	GPIO_SetBits( GPIOA, GPIO_Pin_5 );
}

void PadAFInit( void )
{

	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin		= GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType	= GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd	= GPIO_PuPd_NOPULL;
	
	GPIO_Init( GPIOA, &GPIO_InitStructure );
}

void PadRest( void )
{
	PadOutPutInit( );	//上电先初始化为输出｀
	PadOutPutDown( );	//拉低5ms　放电
	delay_ms( 5 );
	TIM_ClearITPendingBit( TIM2, TIM_IT_CC1 | TIM_IT_Update );
	TIM_SetCounter( TIM2, 0 );
	PadAFInit( );
}

u16 PadGetValue( void )
{
	PadRest( );
	while( TIM_GetFlagStatus(TIM2, TIM_IT_CC1) == RESET )
	{
		if( TIM_GetCounter(TIM2) > (TPAD_ARR_MAX_VAL-500) )
			return TIM_GetCounter(TIM2);
	}
	return TIM_GetCapture1(TIM2);
}

void TIM2_CH1_Cap_Init( u32 arr, u16 psc )
{
	//GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef  TIM2_ICInitStructure;

	RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM2, ENABLE );
	RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOA, ENABLE );

	GPIO_PinAFConfig( GPIOA, GPIO_PinSource5, GPIO_AF_TIM2);
	PadAFInit( );

	TIM_TimeBaseStructure.TIM_Period		= arr;
	TIM_TimeBaseStructure.TIM_Prescaler		= psc; 
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode	= TIM_CounterMode_Up;
	TIM_TimeBaseInit( TIM2, &TIM_TimeBaseStructure );

	TIM2_ICInitStructure.TIM_Channel		= TIM_Channel_1;
	TIM2_ICInitStructure.TIM_ICPolarity		= TIM_ICPolarity_Rising;	
	TIM2_ICInitStructure.TIM_ICSelection	= TIM_ICSelection_DirectTI;	
	TIM2_ICInitStructure.TIM_ICPrescaler	= TIM_ICPSC_DIV1;
	TIM2_ICInitStructure.TIM_ICFilter		= 0x00;
	TIM_ICInit( TIM2, &TIM2_ICInitStructure );

	TIM_Cmd( TIM2, ENABLE );
	
}

void PadInit( u8 psc )
{
	u16 buf[10];
	u32 temp;
	u8  i,j;
	TIM2_CH1_Cap_Init( TPAD_ARR_MAX_VAL, psc-1);

	for(i=0; i<10; i++)
	{
		buf[i] = PadGetValue( );
		delay_ms( 10 );
	}

	for(i=0; i<9; j++)
	{
		for(j=i+1; j<10; j++)
		{
			if(buf[i] > buf[j])
			{
				temp = buf[j];
				buf[j] = buf[i];
				buf[i] = temp;
			}
		}
	}

	temp = 0;
	for(i=2; i<8; i++)
	{
		temp += buf[i];
	}
	PadDefaultValue = temp/6;
	printf("PadDefaultValue is %d\r\n", PadDefaultValue );

	
}

u16 PadGetMaxValue( u8 num )
{
	u16 temp = 0;
	u16 res = 0;

	while(num--)
	{
		temp = PadGetValue( );
		if(temp > res) res = temp;
	}

	return res;
}

u8 PadScan( u8 mode )
{
	u8 sample=3;
	u16 res;
	if( mode == 0 )
	{
		res = PadGetMaxValue( sample );
		if( res > (PadDefaultValue+PADGATEWALL) )
			return PADPULLDOWN;
		else
			return PADPULLUP;
	}
}


