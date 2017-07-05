#include "main.h"
#include <stdio.h>
#define TSADCCON0		0xE1700000
#define TSDATX0			0xE170000C
#define TSDATY0			0xE1700010
//#define CLRINTADC0		0xE1700000
#define ADCMUX			0xE170001C

#define rTSADCCON0		(*(volatile unsigned int *)TSADCCON0)
#define rTSDATX0		(*(volatile unsigned int *)TSDATX0)
#define rTSDATY0		(*(volatile unsigned int *)TSDATY0)
//#define rCLRINTADC0		(*(volatile unsigned int *)CLRINTADC0)
#define rADCMUX			(*(volatile unsigned int *)ADCMUX)




// 初始化ADC控制器的函数
static void adc_init(void)
{
	rTSADCCON0	|= (1<<16);		// resolution set to 12bit
	rTSADCCON0	|= (1<<14);		// enable clock prescaler
	rTSADCCON0 	&= ~(0xFF<<6);
	rTSADCCON0	|= (65<<6);		// convertor clock = 66/66M=1MHz, MSPS=200KHz
	rTSADCCON0 	&= ~(1<<2);		// normal operation mode
	rTSADCCON0 	&= ~(1<<1);		// disable start by read mode
	
	rADCMUX		&= ~(0x0F<<0);	// MUX选择ADCIN0
}

// 注意：第一，延时要确实能延时；第二，延时时间必须合适。  
//限制在本文件之内，只会在adc_test里面调用别的文件不会用；避免冲突！！声明时只需要在main.h中声明adc_test就可以了 
static void delay(void)
{
	volatile unsigned int i, j;
	
	for (i=0; i<4000; i++)
		for (j=0; j<1000; j++);
}


// 测试ADC，完成的功能就是循环检测ADC并得到ADC转换数字值打印出来
void adc_test(void)
{
	unsigned int val = 0;      //比int安全一点
   // float V = 0.0;
	double V = 7.123145,test;
	char byte[4];
	adc_init();
	while (1)
	{
		// 第一步：手工开启ADC转换
		rTSADCCON0	|= (1<<0);
		// 第二步：等待ADC转换完毕
		while (!(rTSADCCON0 & (1<<15)));
		
		// 第三步：读取ADC的数字值
		// 第四步：处理/显示数字值
		val = rTSDATX0;
		printf("x: bit14 = %d.\n", (val & (1<<14)));
       
		printf("x: adc value = %d\n", (val & (0xFFF<<0)));
		//val = val & (0xFFF<<0);
		//V = (5/(2^12)) * val;
		memcpy(byte, &V, sizeof(double));
		printf("%d %d %d %d \n",byte[0],byte[1],byte[2],byte[3]);
		memcpy(&test,byte,sizeof(float));
		printf("result %f \n",test);
		
		printf("x: adc value of the voltage = %lf \n",V);
	
		
		printf("\r\n");
		val = rTSDATY0;
		printf("y: bit14 = %d.\n", (val & (1<<14)));
		printf("y: adc value = %d.\n", (val & (0xFFF<<0)));
        printf("\r\n");
		// 第五步：延时一段
		delay();
	}
	
}






















