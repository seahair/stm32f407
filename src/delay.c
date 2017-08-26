#include "delay.h"

void delay_init( void )
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);//选择外部时钟 HCLK/8
	fac_us=SystemCoreClock/8000000; //为系统时钟的 1/8
	fac_ms=(u16)fac_us*1000;//非 ucos 下,代表每个 ms 需要的 systick 时钟数
}
