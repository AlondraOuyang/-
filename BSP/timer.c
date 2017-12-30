#include "timer.h"
#include "flash.h"
#include "usart.h"
#include "led.h"

#define ARR	100-1
#define PRESCARE	42-1
uint32_t g_writeAdder = 0x0800C004;  //������3��ʼд��
uint32_t g_readAdder = 0x0800C004;   //������3��ʼ����
uint32_t readflash;
extern uint32_t g_ADC_Value;
extern u16 g_flag;
void 
	TIM3_config(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  //84MHz 
	
  TIM_TimeBaseInitStructure.TIM_Period = ARR; 	
	TIM_TimeBaseInitStructure.TIM_Prescaler =PRESCARE ;  
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); 
	
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1; 
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}


void TIM2_config(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);  ///ʹ��TIM2ʱ��
	
  TIM_TimeBaseInitStructure.TIM_Period = ARR; 	
	TIM_TimeBaseInitStructure.TIM_Prescaler=PRESCARE;  //��ʱ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);//��ʼ��TIM2
	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE); //����ʱ��2�����ж�
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn; //��ʱ��2�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1; //��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1; //�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}


/*********��ʱ2��������һ����ʱ���ȡflash�е�ֵת����ģ���ź����*/
void  TIM2_IRQHandler(void)//����
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET)
	{
		if(g_readAdder <=0x080FFFFF)//���flash�е����ݻ�û����
		{
				
			  readflash=STMFLASH_Read(g_readAdder); //��ȡflash�е�����
			
			  DAC_SetChannel2Data(DAC_Align_12b_R,readflash);  //������ȡ������ͨ��DAC���
			  g_readAdder+=4;//��ַ����4��������һ�ζ�ȡ����		
		}
		else
		{
			g_readAdder = 0x0800C004; //���ö�ȡ��ַΪFlash�׵�ַ�������ظ���ȡ
			TIM_Cmd(TIM2,DISABLE);     //�رն�ʱ��2
			turn_led(LED4,OFF);        //Ϩ��LED4����ʾ��ȡ����
		}

		TIM_ClearITPendingBit(TIM2,TIM_IT_Update); 
	}
}


/*******��ʱ��3������һ�����ٶ���flash��д��������*/
void   TIM3_IRQHandler(void)  //�ɼ�
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) //���TIM3���õ���ֵ���
	{
		

    if(g_writeAdder<=0x080FFFFF)//���flash��ûд��
		{
			
		  STMFLASH_Write(g_writeAdder,g_ADC_Value); //��flash����д��ADC�����õ�����g_ADC_Value
			g_writeAdder += 4;//��ַ��4 ��������һ�δ���
		}
		else
			{	
        TIM_Cmd(TIM3,DISABLE);				
				ADC_Cmd(ADC1, DISABLE);
				ADC_DMACmd(ADC1, DISABLE); 
				turn_led(LED2,OFF);//���flash�ڴ��Ѿ�д������Ϩ��LED3
				g_flag = 1;
			}
			
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
	}
}