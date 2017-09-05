#include "capture.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_tim.h"
#include "sys.h"
#include "stm32f4xx_rcc.h"
#include "misc.h"


void TIM5_CH1_Cap_Init(u32 arr,u16 psc)
{	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_ICInitTypeDef TIM5_ICInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE); 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; 
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM5);
	
	TIM_TimeBaseStructure.TIM_Prescaler=psc; 
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 
	TIM_TimeBaseStructure.TIM_Period=arr; 
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseStructure);

	TIM5_ICInitStructure.TIM_Channel = TIM_Channel_1; 
	TIM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising; 
	TIM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; 
	TIM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1; 
	TIM5_ICInitStructure.TIM_ICFilter = 0x00;
	TIM_ICInit(TIM5, &TIM5_ICInitStructure);

	TIM_ITConfig(TIM5,TIM_IT_Update|TIM_IT_CC1,ENABLE);
	TIM_Cmd(TIM5,ENABLE );

	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure); 
}

//捕获状态
//[7]:0,没有成功的捕获;1,成功捕获到一次.
//[6]:0,还没捕获到High电平;1,已经捕获到High电平了.
//[5:0]:捕获低电平后溢出的次数(对于 32 位定时器来说,1us 计数器加 1,溢出时间:4294 秒)

u8 TIM5CH1_CAPTURE_STA;  
u32 TIM5CH1_CAPTURE_VAL;

//static u8 TIM5CH1_CAPTURE_STA=0; //输入捕获状态 
//static u32 TIM5CH1_CAPTURE_VAL;//输入捕获值(TIM2/TIM5 是 32 位)

void TIM5_IRQHandler(void)
{
	printf ("TIM5CH1_CAPTURE_STA = %x \r\n", TIM5CH1_CAPTURE_STA );
	if( (TIM5CH1_CAPTURE_STA & CAPTUREFINISH) == 0 )
	{
		if( TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET )
		{
			if( TIM5CH1_CAPTURE_STA & CAPTUREHIGHLEVEL )
			{
				if( TIM5CH1_CAPTURE_STA & CAPTUREFULL == CAPTUREFULL)
				{
					TIM5CH1_CAPTURE_STA |= CAPTUREFINISH ;
					TIM5CH1_CAPTURE_VAL = 0XFFFFFFFF;
				}
				else
					TIM5CH1_CAPTURE_STA++ ;
			}
   		}
		if( TIM_GetITStatus(TIM5, TIM_IT_CC1) != RESET )
		{
			if( TIM5CH1_CAPTURE_STA & CAPTUREHIGHLEVEL )
			{
				TIM5CH1_CAPTURE_STA |= CAPTUREFINISH ;
				TIM5CH1_CAPTURE_VAL = TIM_GetCapture1(TIM5);
				TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Rising); 
			}
			else{
				TIM5CH1_CAPTURE_STA = 0;
				TIM5CH1_CAPTURE_VAL = 0;
				TIM5CH1_CAPTURE_STA |= CAPTUREHIGHLEVEL ;
				TIM_Cmd(TIM5, ENABLE ); 
				TIM_SetCounter(TIM5, 0);
				TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Falling);
				TIM_Cmd(TIM5,ENABLE ); 
			}
			
		}
	}
	TIM_ClearITPendingBit(TIM5, TIM_IT_CC1|TIM_IT_Update); 
}



u32 Time5CalcCaptureTime( void )
{
	long long temp = 0;
	if(TIM5CH1_CAPTURE_STA&0X80)//成功捕获到了一次高电平
	{
		temp=TIM5CH1_CAPTURE_STA&0X3F; 
		temp*=0XFFFFFFFF; //溢出时间总和
		temp+=TIM5CH1_CAPTURE_VAL; //得到总的高电平时间
		printf("HIGH:%lld us\r\n",temp);//打印总的高点平时间
		TIM5CH1_CAPTURE_STA=0; //开启下一次捕获
		return temp;
	}
	else
		return 0;
}



/*
TIM_ICInitTypeDef  TIM5_ICInitStructure;

//¶šÊ±Æ÷5ÍšµÀ1ÊäÈë²¶»ñÅäÖÃ
//arr£º×Ô¶¯ÖØ×°Öµ(TIM2,TIM5ÊÇ32Î»µÄ!!)
//psc£ºÊ±ÖÓÔ€·ÖÆµÊý
void TIM5_CH1_Cap_Init(u32 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);  	//TIM5Ê±ÖÓÊ¹ÄÜ    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//Ê¹ÄÜPORTAÊ±ÖÓ	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; //GPIOA0
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//žŽÓÃ¹ŠÄÜ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//ËÙ¶È100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //ÍÆÍìžŽÓÃÊä³ö
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; //ÏÂÀ­
	GPIO_Init(GPIOA,&GPIO_InitStructure); //³õÊŒ»¯PA0

	GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM5); //PA0žŽÓÃÎ»¶šÊ±Æ÷5
  
	  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //¶šÊ±Æ÷·ÖÆµ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //ÏòÉÏŒÆÊýÄ£Êœ
	TIM_TimeBaseStructure.TIM_Period=arr;   //×Ô¶¯ÖØ×°ÔØÖµ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseStructure);
	

	//³õÊŒ»¯TIM5ÊäÈë²¶»ñ²ÎÊý
	TIM5_ICInitStructure.TIM_Channel = TIM_Channel_1; //CC1S=01 	Ñ¡ÔñÊäÈë¶Ë IC1Ó³ÉäµœTI1ÉÏ
  TIM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//ÉÏÉýÑØ²¶»ñ
  TIM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //Ó³ÉäµœTI1ÉÏ
  TIM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //ÅäÖÃÊäÈë·ÖÆµ,²»·ÖÆµ 
  TIM5_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 ÅäÖÃÊäÈëÂË²šÆ÷ ²»ÂË²š
  TIM_ICInit(TIM5, &TIM5_ICInitStructure);
		
	TIM_ITConfig(TIM5,TIM_IT_Update|TIM_IT_CC1,ENABLE);//ÔÊÐížüÐÂÖÐ¶Ï ,ÔÊÐíCC1IE²¶»ñÖÐ¶Ï	
	
  TIM_Cmd(TIM5,ENABLE ); 	//Ê¹ÄÜ¶šÊ±Æ÷5

 
  NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//ÇÀÕŒÓÅÏÈŒ¶3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;		//×ÓÓÅÏÈŒ¶3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQÍšµÀÊ¹ÄÜ
	NVIC_Init(&NVIC_InitStructure);	//žùŸÝÖž¶šµÄ²ÎÊý³õÊŒ»¯VICŒÄŽæÆ÷¡¢
	
	
}
//²¶»ñ×ŽÌ¬
//[7]:0,Ã»ÓÐ³É¹ŠµÄ²¶»ñ;1,³É¹Š²¶»ñµœÒ»ŽÎ.
//[6]:0,»¹Ã»²¶»ñµœµÍµçÆœ;1,ÒÑŸ­²¶»ñµœµÍµçÆœÁË.
//[5:0]:²¶»ñµÍµçÆœºóÒç³öµÄŽÎÊý(¶ÔÓÚ32Î»¶šÊ±Æ÷ÀŽËµ,1usŒÆÊýÆ÷ŒÓ1,Òç³öÊ±Œä:4294Ãë)
static u8  TIM5CH1_CAPTURE_STA=0;	//ÊäÈë²¶»ñ×ŽÌ¬		    		
static u32	TIM5CH1_CAPTURE_VAL;	//ÊäÈë²¶»ñÖµ(TIM2/TIM5ÊÇ32Î»)
//¶šÊ±Æ÷5ÖÐ¶Ï·þÎñ³ÌÐò	 
void TIM5_IRQHandler(void)
{ 		    

 	if((TIM5CH1_CAPTURE_STA&0X80)==0)//»¹ÎŽ³É¹Š²¶»ñ	
//	if(1)
	{
		if(TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)//Òç³ö
		{	     
			if(TIM5CH1_CAPTURE_STA&0X40)//ÒÑŸ­²¶»ñµœžßµçÆœÁË
			{
				if((TIM5CH1_CAPTURE_STA&0X3F)==0X3F)//žßµçÆœÌ«³€ÁË
				{
					TIM5CH1_CAPTURE_STA|=0X80;		//±êŒÇ³É¹Š²¶»ñÁËÒ»ŽÎ
					TIM5CH1_CAPTURE_VAL=0XFFFFFFFF;
				}else TIM5CH1_CAPTURE_STA++;
			}	 
		}
		if(TIM_GetITStatus(TIM5, TIM_IT_CC1) != RESET)//²¶»ñ1·¢Éú²¶»ñÊÂŒþ
		{	
			if(TIM5CH1_CAPTURE_STA&0X40)		//²¶»ñµœÒ»žöÏÂœµÑØ 		
			{	  			
				TIM5CH1_CAPTURE_STA|=0X80;		//±êŒÇ³É¹Š²¶»ñµœÒ»ŽÎžßµçÆœÂö¿í
			  TIM5CH1_CAPTURE_VAL=TIM_GetCapture1(TIM5);//»ñÈ¡µ±Ç°µÄ²¶»ñÖµ.
	 			TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Rising); //CC1P=0 ÉèÖÃÎªÉÏÉýÑØ²¶»ñ
			}else  								//»¹ÎŽ¿ªÊŒ,µÚÒ»ŽÎ²¶»ñÉÏÉýÑØ
			{
				TIM5CH1_CAPTURE_STA=0;			//Çå¿Õ
				TIM5CH1_CAPTURE_VAL=0;
				TIM5CH1_CAPTURE_STA|=0X40;		//±êŒÇ²¶»ñµœÁËÉÏÉýÑØ
				TIM_Cmd(TIM5,DISABLE ); 	//¹Ø±Õ¶šÊ±Æ÷5
	 			TIM_SetCounter(TIM5,0);
	 			TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Falling);		//CC1P=1 ÉèÖÃÎªÏÂœµÑØ²¶»ñ
				TIM_Cmd(TIM5,ENABLE ); 	//Ê¹ÄÜ¶šÊ±Æ÷5
			}		    
		}			     	    					   
 	}
	TIM_ClearITPendingBit(TIM5, TIM_IT_CC1|TIM_IT_Update); //Çå³ýÖÐ¶Ï±êÖŸÎ»
}
*/
