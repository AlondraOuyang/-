#ifndef __LED_H
#define __LED_H

#include "stm32f10x.h"

#define LED_2 PFout(7)	// DS0
#define LED_3 PFout(8)	// DS1	
#define LED_4 PFout(9)	// DS0
#define LED_5 PFout(10)	// DS1	 

#define ON	1
#define OFF	0
#define LED_STATUS 0

enum
{
	LED2 = 0,
	LED3 = 1,
	LED4 = 2,
	LED5 = 3,
	MAX_LED,
};

typedef struct led_gpio_s
{
	int num; 	              /*led���*/
	GPIO_TypeDef	*group;   /*LEDʹ�õ�����һ��GPIO*/
	u16	pin;                /*LEDʹ�õ�GPIO������һ��pin*/
}led_gpio_t;

extern void Init_LED_GPIO(void);
extern void turn_led(int whitch,int cmd);
extern void twinkle_led(int witch);
#endif

