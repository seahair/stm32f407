#ifndef __EXTI_H
#define __EXIT_H	 
#include "sys.h"  	
#include "stm32f4xx_syscfg.h"
#include "stm32f4xx_exti.h"

#define EXTI_KEY0 		      EXTI_PinSource4    //GPIOE 
#define EXTI_KEY1 		      EXTI_PinSource3    //GPIOE 
#define EXTI_KEY2 		      EXTI_PinSource2    //GPIOE 
#define EXTI_WK_UP 	          EXTI_PinSource0    //GPIOA


#define EXTI_LINE_KEY0 		      EXTI_Line4    //GPIOE 
#define EXTI_LINE_KEY1 		      EXTI_Line3    //GPIOE 
#define EXTI_LINE_KEY2 		      EXTI_Line2    //GPIOE 
#define EXTI_LINE_WK_UP 	      EXTI_Line0    //GPIOA


void EXTIX_Init(void);	//外部中断初始化		 					    
#endif

























