#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h" 


#define KEY0 		      GPIO_Pin_4    //GPIOE 
#define KEY1 		      GPIO_Pin_3    //GPIOE 
#define KEY2 		      GPIO_Pin_2    //GPIOE 
#define WK_UP 	          GPIO_Pin_0    //GPIOA


#define KEY0_ACTIVE       1
#define KEY1_ACTIVE 	  2
#define KEY2_ACTIVE  	  3
#define WKUP_ACTIVE       4

#define KEY0_PRESS        0
#define KEY1_PRESS        0
#define KEY2_PRESS        0
#define KEY_WK_UP_PRESS   1

#define KEY0_RELEASE      1
#define KEY1_RELEASE      1
#define KEY2_RELEASE      1
#define KEY_WK_UP_RELEASE 0

void KEY_Init(void);	//IO初始化
// u8 KEY_Scan(u8);  		//按键扫描函数
void KeyTest( void );
u8 GetKEY0Status( void );
u8 GetKEY1Status( void );
u8 GetKEY2Status( void );
u8 GetKEYWKUPStatus( void );

#endif
