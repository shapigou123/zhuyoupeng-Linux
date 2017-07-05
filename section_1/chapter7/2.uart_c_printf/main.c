#include "stdio.h"

void uart_init(void);
#if 0
void delay(void)
{
	volatile unsigned int i = 900000;		// volatile 让编译器不要优化，这样才能真正的减
	while (i--);							// 才能消耗时间，实现delay
}
#endif

int main(void)
{
	uart_init();
	
	int a = 12345678;
	putc('a');
	putc('b');
	putc('c');

	while (1)
	{
		printf("test for printf, a = %d.\n", a);
		//delay();
		//delay();
	}
	
	/*
	while(1)
	{
		uart_putc('a');
		delay();
	}
	*/
	return 0;
}