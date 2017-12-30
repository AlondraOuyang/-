#ifndef __KEY_H
#define __KEY_H
#include "stm32f10x.h"

typedef struct key_gpio_s
{
	int num;
	GPIO_TypeDef *group;
	u16 pin;	
}key_gpio_t;

enum {
	KEY1=0,
	KEY2=1,
	KEY3=2,
	MAX_KEY,
};

void key_config(void);
u8 key_pressed(int witch);


#endif

