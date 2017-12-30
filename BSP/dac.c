

#include "dac.h"

void  DAC_config(void)
{
	GPIO_InitTypeDef      GPIO_InitStructure;
	DAC_InitTypeDef       DAC_InitType;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//ʹ�� PA ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);//ʹ�� DAC ʱ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; //PA5
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;//ģ������
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//����
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ�� GPIO
	
	DAC_InitType.DAC_Trigger = DAC_Trigger_None; //��ʹ�ô������� TEN1=0
	DAC_InitType.DAC_WaveGeneration = DAC_WaveGeneration_None;//��ʹ�ò��η���
	DAC_InitType.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0;//���Ρ���ֵ����			
	DAC_InitType.DAC_OutputBuffer = DAC_OutputBuffer_Disable ;//�������ر�
	DAC_Init(DAC_Channel_2,&DAC_InitType); //��ʼ�� DAC ͨ�� 2
	DAC_Cmd(DAC_Channel_2, ENABLE); //ʹ�� DAC ͨ�� 1
		
}


