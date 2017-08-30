#include "pwm.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_tim.h"
#include "sys.h"
#include "stm32f4xx_rcc.h"



void TIM14_PWM_Init(u32 arr,u32 psc)
{		 					 
	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14,ENABLE); 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	
	GPIO_PinAFConfig(GPIOF,GPIO_PinSource9,GPIO_AF_TIM14);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;           
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        
	GPIO_Init(GPIOF,&GPIO_InitStructure);              
	  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //Tout= ((arr+1)*(psc+1))/Tclk
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period=arr;   //×Ô¶¯ÖØ×°ÔØÖµ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(PWMTIME, &TIM_TimeBaseStructure);//³õÊŒ»¯¶šÊ±Æ÷14
	
	//³õÊŒ»¯TIM14 Channel1 PWMÄ£Êœ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OC1Init(PWMTIME, &TIM_OCInitStructure);  

	TIM_OC1PreloadConfig(PWMTIME, TIM_OCPreload_Enable);
 
	TIM_ARRPreloadConfig(PWMTIME,ENABLE);
	
	TIM_Cmd(PWMTIME, ENABLE);  
 
										  
}  

void Time4PwmInit_HZ( u32 hz )
{
	TIM14_PWM_Init(1000000/hz-1, 84-1);
}

void Time4PwmSetDuty( u16 duty )
{
	TIM_SetCompare1(PWMTIME, duty);
}

void Time4PwmDutyIncrease( u16 step )
{
	if( step < PWMCYCLE )
		Time4PwmSetDuty( (TIM_GetCapture1(PWMTIME)+step)%PWMCYCLE ) ;
}

void Time4PwmDutyDecrease( u16 step )
{
	if( step<PWMCYCLE && step< TIM_GetCapture1(PWMTIME) )
		Time4PwmSetDuty( TIM_GetCapture1(PWMTIME) - step ) ;
}

void PwmTest( void )
{
	u16 led0pwmval=0;
	u8 dir=1;
	if(dir)led0pwmval++;//dir==1 led0pwmval 递增
	else led0pwmval--; //dir==0 led0pwmval 递减
	if(led0pwmval>300)dir=0;//led0pwmval 到达 300 后，方向为递减
	if(led0pwmval==0)dir=1; //led0pwmval 递减到 0 后，方向改为递增
	Time4PwmSetDuty( led0pwmval ); //修改比较值，修改占空
}

void PwmTestDuty( void )
{
	Time4PwmDutyIncrease( 2 );
}

