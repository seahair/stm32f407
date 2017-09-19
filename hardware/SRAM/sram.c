#include "sram.h"
#include "stm32f4xx_fsmc.h"
#include "stm32f4xx_gpio.h"



#define Bank1_SRAM3_ADDR	((u32) (0x68000000))

void FSMC_SRAM_Init( void )
{
	GPIO_InitTypeDef				GPIO_InitStructure;
	FSMC_NORSRAMInitTypeDef			FSMC_NORSRAMInitStrure;
	FSMC_NORSRAMTimingInitTypeDef	readWriteTiming;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOD|
				RCC_AHB1Periph_GPIOE|RCC_AHB1Periph_GPIOF|RCC_AHB1Periph_GPIOG,
																		ENABLE);

	RCC_AHB3PeriphClockCmd( RCC_AHB3Periph_FSMC, ENABLE );

	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//设置速度
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;		//设置上拉
	GPIO_Init(GPIOB, &GPIO_InitStructure);	

	GPIO_InitStructure.GPIO_Pin   = (3<<0)|(3<<4)|(0XFF<<8);
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//设置速度
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;		//设置上拉
	GPIO_Init(GPIOD, &GPIO_InitStructure);	
	

	GPIO_PinAFConfig(GPIOD,GPIO_PinSource0,GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource1,GPIO_AF_FSMC);
	
	GPIO_PinAFConfig(GPIOG,GPIO_PinSource5,GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOG,GPIO_PinSource10,GPIO_AF_FSMC);

	readWriteTiming.FSMC_AddressSetupTime			= 0x00;
	readWriteTiming.FSMC_AddressHoldTime			= 0x00;
	readWriteTiming.FSMC_DataSetupTime				= 0x08;
	readWriteTiming.FSMC_BusTurnAroundDuration		= 0x00;
	readWriteTiming.FSMC_CLKDivision				= 0x00;
	readWriteTiming.FSMC_DataLatency				= 0x00;
	readWriteTiming.FSMC_AccessMode		= FSMC_AccessMode_A;

	FSMC_NORSRAMInitStrure.FSMC_Bank	= FSMC_Bank1_NORSRAM3;
	FSMC_NORSRAMInitStrure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
	FSMC_NORSRAMInitStrure.FSMC_MemoryType	   = FSMC_MemoryType_SRAM;
	FSMC_NORSRAMInitStrure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
	FSMC_NORSRAMInitStrure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
	FSMC_NORSRAMInitStrure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
	FSMC_NORSRAMInitStrure.FSMC_AsynchronousWait   = FSMC_AsynchronousWait_Disable;
	FSMC_NORSRAMInitStrure.FSMC_WrapMode		= FSMC_WrapMode_Disable;
	FSMC_NORSRAMInitStrure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
	FSMC_NORSRAMInitStrure.FSMC_WriteOperation  = FSMC_WriteOperation_Enable;
	FSMC_NORSRAMInitStrure.FSMC_WaitSignal		= FSMC_WaitSignal_Disable;
	FSMC_NORSRAMInitStrure.FSMC_ExtendedMode	= FSMC_ExtendedMode_Disable;
	FSMC_NORSRAMInitStrure.FSMC_WriteBurst		= FSMC_WriteBurst_Disable;
	FSMC_NORSRAMInitStrure.FSMC_ReadWriteTimingStruct = &readWriteTiming;
	FSMC_NORSRAMInitStrure.FSMC_WriteTimingStruct	= &readWriteTiming;

	FSMC_NORSRAMInit( &FSMC_NORSRAMInitStrure );
	FSMC_NORSRAMCmd( FSMC_Bank1_NORSRAM3, ENABLE );
	
}

void FSMC_SRAM_WriteBuffer( u8* pBuffer, u32 WriteAddr, u32 n )
{
	for( ; n!=0; n-- )
	{
		*(vu8*) (Bank1_SRAM3_ADDR + WriteAddr) = *pBuffer;
		WriteAddr++;
		pBuffer++;
	}
}

void FSMC_SRAM_ReadBuffer( u8* pBuffer, u32 ReadAddr, u32 n )
{
	for( ; n!=0; n-- )
	{
		*pBuffer = *(vu8*) (Bank1_SRAM3_ADDR + ReadAddr);
		ReadAddr++;
	}
}
