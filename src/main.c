#include "stm32f4xx.h"
#include "led.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_flash.h"
#include "usart.h"
#include "beep.h"
#include "key.h"
#include "delay.h"
#include <stdio.h>
#include <stdlib.h>

void HardInit( void );
int _write(int fd, char *ptr, int len);


int main(int argc, char *argv[])
{
	HardInit();
	KEY_Init();      


	u8 test[] = {'h', 'e', 'l', 'l', 'o', '\r','\n'};
	while(1)
	{
		u8 t;
		for(t=0;t<7;t++)
		{
			USART_SendData(USART1, test[t]);
			while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
		}
		
		KeyTest();
		LedBlink( LedRed );

		printf ("hello world\n");
		//BeepAlarm( 500 );

	}
}

	
void HardInit( void )
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init( 168 );
	LedInit( LedRed );
	LedInit( LedGreen );	
	BEEP_Init();
	uart_init(115200);	
}

/*
int _write(int fd, char *ptr, int len)
{
	int i = 0;


	 //write "len" of char from "ptr" to file id "fd"
	 //Return number of char written.
	 //Only work for STDOUT, STDIN, and STDERR

	if (fd > 2)
	{
		return -1;
	}

	while (*ptr && (i < len))
	{
		USART_SendData(USART1, *ptr);
		//usart_send_blocking(USART1, *ptr);

		if (*ptr == '\n')
		{
			USART_SendData(USART1, '\r');
			//usart_send_blocking(USART1, '\r');
		}

		i++;
		ptr++;
	}

	return i;
}*/

int _write (int fd, char *pBuffer, int size)  
{  
	for (int i = 0; i < size; i++)  
	{  
		while (!(USART1->SR & USART_SR_TXE))  
		{  
		}  
		USART_SendData(USART1, pBuffer[i]);  
	}  
	return size;  
}  
int _read (int fd, char *pBuffer, int size)  
{  
	for (int i = 0; i < size; i++)  
	{  
		while ((USART1->SR & USART_SR_RXNE) == 0)  
		{  
		}  
  
		pBuffer[i] = USART_ReceiveData(USART1);  
	}  
	return size;  
} 
