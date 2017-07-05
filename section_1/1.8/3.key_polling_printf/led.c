
#define GPJ0CON     0xE0200240
#define GPJ0DAT     0xE0200244
//#define GPD0CON     0xE02000A0
//#define GPD0DAT     0xE02000A4
#define rGPJ0CON    (*(volatile unsigned int *)GPJ0CON)
#define rGPJ0DAT    (*(volatile unsigned int *)GPJ0DAT)  

void _delay(void)
{
	volatile unsigned int i=3000000;   //让编译器不要优化，才能真正自减，才能真正消耗时间；
	while(i--);
}

void led_blink(void)
{
	rGPJ0CON=0x11111111; 
	//volatile unsigned int *p=(unsigned int*)GPJ0CON;
	//volatile unsigned int *p1=(unsigned int*)GPJ0DAT;
	//*p=0x11111111;
	
	while(1)
	{
		
		rGPJ0DAT =((0<<3) | (0<<4) | (0<<5));
		_delay();
		rGPJ0DAT =((1<<3) | (1<<4) | (1<<5));
		_delay();
	}
	
}

void led_off(void)
{
	rGPJ0CON=0x11111111; 
	rGPJ0DAT =((1<<3) | (1<<4) | (1<<5));
}
/*
void led1(void)
{
	rGPJ0CON = 0x11111111;
	rGPJ0DAT = ((0<<3) | (1<<4) | (1<<5));
}
*/

void led1_on(void)
{
	rGPJ0CON=0x11111111; 
	rGPJ0DAT =((0<<3) | (1<<4) | (1<<5));
}

void led2_on(void)
{
	rGPJ0CON=0x11111111; 
	rGPJ0DAT =((0<<3) | (0<<4) | (1<<5));
}

void led3_on(void)
{
	rGPJ0CON=0x11111111; 
	rGPJ0DAT =((0<<3) | (0<<4) | (0<<5));
}

void led_blink1()
{
	    rGPJ0CON=0x11111111; 
	    rGPJ0DAT =((0<<3) | (0<<4) | (0<<5));
		_delay();
		rGPJ0DAT =((1<<3) | (1<<4) | (1<<5));
		_delay();
	
}



#if 0
       // 第一步： 把0x11111111写入0xE0200240（GPJ0CON）位置
	   ldr r0, =0x11111111        //伪指令
	   ldr r1, =GPJ0CON           //一般写代码都用伪指令，可以自动判断合法非法并处理！
	   str r0, [r1]               //寄存机间接寻址，把r0中的数写入r1中的数为地址的内存中去！
	   
	   ldr r0, =0x00000010
	   ldr r1, =GPD0CON
	   str r0, [r1]
	   
flash:   
	   // 第二步： 写入0xE0200244(GPJ0DAT)位置
	   
	  // ldr r0,=0x10
	  
	   //全灭
	  // ldr r0, = (1<<3) | (1<<4) | (1<<5)
	   ldr r0, = 0xff
	   ldr r1, =GPJ0DAT
	   str r0, [r1]   
	 
	   ldr r0, = (1<<1)
	   ldr r1, =GPD0DAT
	   str r0, [r1]
	   bl _delay
	   
	   //LED4亮
	   ldr r0, = ~(1<<1)
	   ldr r1, =GPD0DAT
	   str r0, [r1]
	   bl _delay
	   
	   ldr r0, = (1<<1)
	   ldr r1, =GPD0DAT
	   str r0, [r1]	   
	   
	   //LED3亮
	   ldr r0, = ~(1<<5)
	   ldr r1, =GPJ0DAT
	   str r0, [r1]
	   bl _delay
	   
	   //LED2亮,同时LED3灭
	   ldr r0, = ~(1<<4)
	   ldr r1, =GPJ0DAT
	   str r0, [r1]
	   bl _delay
	   
	   //LED1亮
	   ldr r0, = ~(1<<3)
	   ldr r1, =GPJ0DAT
	   str r0, [r1]
	   bl _delay
	   
	   //全亮
	   ldr r0, = 0x00
	   ldr r1, =GPJ0DAT
	   str r0, [r1]
	   
	   ldr r0, = ~(1<<1)
	   ldr r1, =GPD0DAT
	   str r0, [r1]
	   
	   bl _delay
	   
	   b flash
	   
	   
	b .                           // .代表当前这一句指令的地址，也是死循环      
//flag:                            
//     b flag                       //写了一个死循环。因为裸机程序是直接在CPU上运行的，
                                  //CPU会逐行运行裸机程序直到CPU断电关机，如果我们的程序所有的代码都执行完了
								  //CPU就会跑飞跑飞以后是未定义的，所以千万不能让CPU跑飞），
   							      //不让CPU跑飞的办法就是在我们整个程序执行完后添加死循环
								  //b 为跳转指令，原地打转
								
								
_delay:
	  ldr r2, =20000000
	  ldr r3, =0x0
delay_loop:
      sub r2,r2, #1
	  cmp r2, r3                  //r2=r3,则Z标志位=1， 下一句eq就会成立
	  bne delay_loop
	  mov pc, lr                  //函数返回
	  
	  
#endif