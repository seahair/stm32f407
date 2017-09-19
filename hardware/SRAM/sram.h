#ifndef	 __SRAM_H__
#define  __SRAM_H__

#include "sys.h"

void FSMC_SRAM_Init( void );
void FSMC_SRAM_WriteBuffer( u8* pBuffer, u32 WriteAddr, u32 n );
void FSMC_SRAM_ReadBuffer( u8* pBuffer, u32 ReadAddr, u32 n );



#endif
