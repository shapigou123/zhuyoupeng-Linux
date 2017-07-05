/*
 *  �ļ����� led.s
 *  ���ߣ�   ����
 *  ������   ����LED�ĵ�һ���������
 */
 
#define GPJ0CON  0xE0200240
#define GPJ0DAT  0xE0200244
.global _start 
_start:
       // ��һ���� ��0x11111111д��0xE0200240��GPJ0CON��λ��
	   ldr r0, =0x00111000        //αָ��
	   ldr r1, =GPJ0CON           //һ��д���붼��αָ������Զ��жϺϷ��Ƿ���������
	   str r0, [r1]               //�Ĵ�����Ѱַ����r0�е���д��r1�е���Ϊ��ַ���ڴ���ȥ��
flash:   
	   // �ڶ����� д��0xE0200244(GPJ0DAT)λ��
	   
	  // ldr r0,=0x10
	  
	   //ȫ��
	   ldr r0, = (1<<3) | (1<<4) | (1<<5)
	   ldr r1, =GPJ0DAT
	   str r0, [r1]
	   bl _delay
	   
	   //LED3��
	   ldr r0, = (1<<3) | (1<<4) | (0<<5)
	   ldr r1, =GPJ0DAT
	   str r0, [r1]
	   bl _delay
	   
	   //LED2��
	   ldr r0, = (1<<3) | (0<<4) | (1<<5)
	   ldr r1, =GPJ0DAT
	   str r0, [r1]
	   bl _delay
	   
	   //LED1��
	   ldr r0, = (0<<3) | (1<<4) | (1<<5)
	   ldr r1, =GPJ0DAT
	   str r0, [r1]
	   bl _delay
	   
	   //ȫ��
	   ldr r0, = (0<<3) | (0<<4) | (0<<5)
	   ldr r1, =GPJ0DAT
	   str r0, [r1]
	   bl _delay
	   
	   b flash
	   
	   
	b .                           // .������ǰ��һ��ָ��ĵ�ַ��Ҳ����ѭ��      
//flag:                            
//     b flag                       //д��һ����ѭ������Ϊ���������ֱ����CPU�����еģ�
                                  //CPU�����������������ֱ��CPU�ϵ�ػ���������ǵĳ������еĴ��붼ִ������
								  //CPU�ͻ��ܷ��ܷ��Ժ���δ����ģ�����ǧ������CPU�ܷɣ���
   							      //����CPU�ܷɵİ취������������������ִ�����������ѭ��
								  //b Ϊ��תָ�ԭ�ش�ת
								
								
_delay:
	  ldr r2, =20000000
	  ldr r3, =0x0
delay_loop:
      sub r2, r2, #1
	  cmp r2, r3                  //r2=r3,��Z��־λ=1�� ��һ��eq�ͻ����
	  bne delay_loop
	  mov pc, lr                  //��������
	  
	  
	  