#define GPA0CON       0xE0200000
#define UCON0         0xE2900004
#define ULCON0        0xE2900000
#define UMCON0        0xE290000C
#define UFCON0        0xE2900008
#define UBRDIV0       0xE2900028
#define UDIVSLOT0     0xE290002C
#define UTRSTAT0      0xE2900010
#define UTXH0         0xE2900020
#define URXH0         0xE2900024

#define rGPA0CON        (*(volatile unsigned int *)GPA0CON)
#define rUCON0          (*(volatile unsigned int *)UCON0)
#define rULCON0         (*(volatile unsigned int *)ULCON0)
#define rUMCON0         (*(volatile unsigned int *)UMCON0)
#define rUFCON0         (*(volatile unsigned int *)UFCON0)
#define rUBRDIV0        (*(volatile unsigned int *)UBRDIV0)
#define rUDIVSLOT0      (*(volatile unsigned int *)UDIVSLOT0)
#define rUTRSTAT0       (*(volatile unsigned int *)UTRSTAT0)
#define rUTXH0          (*(volatile unsigned int *)UTXH0)
#define rURXH0          (*(volatile unsigned int *)URXH0)

//串口初始化
void uart_init(void)
{
	rGPA0CON &=(0xff);
    rGPA0CON |= 0x00000022;
	rULCON0 = 0x3;
	rUCON0 = 0x5;
	rUMCON0 = 0x0;
	rUFCON0 = 0x0;
	
	
	rUBRDIV0 = 35;   //余数0.18
	rUDIVSLOT0 =0x0888;    //0.18*16
	

	}


//发送一个字节
void uart_putc(char c)
{
	while(!(rUTRSTAT0 & (1<<1)));
	rUTXH0 = c;
	
}

//接受
char uart_getc(void)
{
	while(!(rUTRSTAT0 & (1<<0)));
	return rURXH0 & 0x0f;
	
}