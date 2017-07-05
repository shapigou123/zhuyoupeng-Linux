/*
 *  文件名： led.s
 *  作者：   余杨
 *  描述：   点亮LED的第一个裸机程序
 */
 
#define GPJ0CON  0xE0200240
#define GPJ0DAT  0xE0200244
.global _start 
_start:
       // 第一步： 把0x11111111写入0xE0200240（GPJ0CON）位置
	   ldr r0, =0x00111000        //伪指令
	   ldr r1, =GPJ0CON           //一般写代码都用伪指令，可以自动判断合法非法并处理！
	   str r0, [r1]               //寄存机间接寻址，把r0中的数写入r1中的数为地址的内存中去！
flash:   
	   // 第二步： 写入0xE0200244(GPJ0DAT)位置
	   
	  // ldr r0,=0x10
	  
	   //全灭
	   ldr r0, = (1<<3) | (1<<4) | (1<<5)
	   ldr r1, =GPJ0DAT
	   str r0, [r1]
	   bl _delay
	   
	   //LED3亮
	   ldr r0, = (1<<3) | (1<<4) | (0<<5)
	   ldr r1, =GPJ0DAT
	   str r0, [r1]
	   bl _delay
	   
	   //LED2亮
	   ldr r0, = (1<<3) | (0<<4) | (1<<5)
	   ldr r1, =GPJ0DAT
	   str r0, [r1]
	   bl _delay
	   
	   //LED1亮
	   ldr r0, = (0<<3) | (1<<4) | (1<<5)
	   ldr r1, =GPJ0DAT
	   str r0, [r1]
	   bl _delay
	   
	   //全亮
	   ldr r0, = (0<<3) | (0<<4) | (0<<5)
	   ldr r1, =GPJ0DAT
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
      sub r2, r2, #1
	  cmp r2, r3                  //r2=r3,则Z标志位=1， 下一句eq就会成立
	  bne delay_loop
	  mov pc, lr                  //函数返回
	  
	  
	  