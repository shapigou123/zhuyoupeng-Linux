/*
 *  文件名： start.s
 *  作者：   余杨
 *  描述：   点亮LED的第一个裸机程序
 */
 

#define WTCON       0xE2700000
#define SVC_STACK   0xD0037D80
.global _start 
_start:


	// 第0步：开发板置锁
	// 写法1
	//ldr r0, =0xE010E81C
	//ldr r1, =0x301
	//str r1, [r0]
	// 写法2
	//ldr r0, =0xE010E81C
	//ldr r1, [r0]
	//orr r1, r1, #0x300
	//orr r1, r1, #0x01
	//str r1, [r0]
	// 写法3
	ldr r0, =0xE010E81C
	ldr r1, [r0]
	ldr r2, =0x301
	orr r1, r1, r2
	str r1, [r0]
       //第1步 关看门狗，越早越好，与在前越好；越晚，若程序执行时间过长，则程序被复位的可能性越大。
     
	   ldr r0, =WTCON
       ldr r1, =0x0
       str r1, [r0]	   
	   
	   //第2步设置svc栈
	   
	   ldr sp, =SVC_STACK
	   
	   	// 第3步：开/关icache
	   mrc p15,0,r0,c1,c0,0;			// 读出cp15的c1到r0中
	   //bic r0, r0, #(1<<12)			// bit12 置0  关icache
	   orr r0, r0, #(1<<12)			// bit12 置1  开icache
	   mcr p15,0,r0,c1,c0,0;

	   
	   //从这之后就可以用C语言执行了！！
	   bl key_init
	   bl key_polling
	  // bl led_blink
	   
	   // 汇编最后的这个死循环不能丢
	   b .
	
	  