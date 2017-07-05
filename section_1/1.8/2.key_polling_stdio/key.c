#include "stdio.h"

#define GPH0CON		0xE0200C00
#define GPH0DAT		0xE0200C04

#define GPH2CON		0xE0200C40
#define GPH2DAT		0xE0200C44

#define rGPH0CON	(*(volatile unsigned int *)GPH0CON)
#define rGPH0DAT	(*(volatile unsigned int *)GPH0DAT)
#define rGPH2CON	(*(volatile unsigned int *)GPH2CON)
#define rGPH2DAT	(*(volatile unsigned int *)GPH2DAT)


void key_init(void)
{
	rGPH0CON = 0x0;
	rGPH2CON = 0x0;
	
		// ����GPHxCON�Ĵ���������Ϊ����ģʽ
	// GPH0CON��bit8��15ȫ������Ϊ0������
	//rGPH0CON &= ~(0xFF<<8);
	// GPH2CON��bit0��15ȫ������Ϊ0������
	//rGPH2CON &= ~(0xFFFF<<0);
}

void key_polling(void)
{
	while(1)
	{
		if(rGPH0DAT & (1<<2))
		{
			led_off();
			//printf("key left down!\n");
		}  	
		else
		{
			led1();
			printf("key left on!\n");
		}
		
		if(rGPH0DAT & (1<<3))
		{
			led_off();
		}  	
		else
		{
			led2();
			printf("key down on!\n");
		}
		
		if(rGPH2DAT & (1<<1))
		{
			led_off();
		}  	
		else
		{
			led3();
			printf("key up on!\n");
		}
		

	}
}