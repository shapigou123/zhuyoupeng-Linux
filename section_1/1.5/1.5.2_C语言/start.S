/*
 *  文件名： led.s
 *  作者：   余杨
 *  描述：   点亮LED的第一个裸机程序
 */
 

#define WTCON       0xE2700000
#define SVC_STACK   0xD0037D80
.global _start 
_start:

       //关看门狗，越早越好，与在前越好；越晚，若程序执行时间过长，则程序被复位的可能性越大。
     
	   ldr r0, =WTCON
       ldr r1, =0x0
       str r1, [r0]	   
	   
	   //设置svc栈
	   
	   ldr sp, =SVC_STACK
	   
	   //从这之后就可以用C语言执行了！！
	   
	   bl led_blink
	   
	   // 汇编最后的这个死循环不能丢
	   b .
	
	  