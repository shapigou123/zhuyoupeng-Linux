#include <stdio.h>
void main(void)
{
	uart_init();
	while(1)
	{
	uart_putc('A');
	delay();
	uart_putc('B');
	delay();
	}
	
}

