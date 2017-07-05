
#define GPJ0CON     0xE0200240
#define GPJ0DAT     0xE0200244
//#define GPD0CON     0xE02000A0
//#define GPD0DAT     0xE02000A4
#define rGPJ0CON    (*(volatile unsigned int *)GPJ0CON)
#define rGPJ0DAT    (*(volatile unsigned int *)GPJ0DAT)  

void _delay(void)
{
	volatile unsigned int i=3000000;   //�ñ�������Ҫ�Ż������������Լ���������������ʱ�䣻
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
       // ��һ���� ��0x11111111д��0xE0200240��GPJ0CON��λ��
	   ldr r0, =0x11111111        //αָ��
	   ldr r1, =GPJ0CON           //һ��д���붼��αָ������Զ��жϺϷ��Ƿ�������
	   str r0, [r1]               //�Ĵ�����Ѱַ����r0�е���д��r1�е���Ϊ��ַ���ڴ���ȥ��
	   
	   ldr r0, =0x00000010
	   ldr r1, =GPD0CON
	   str r0, [r1]
	   
flash:   
	   // �ڶ����� д��0xE0200244(GPJ0DAT)λ��
	   
	  // ldr r0,=0x10
	  
	   //ȫ��
	  // ldr r0, = (1<<3) | (1<<4) | (1<<5)
	   ldr r0, = 0xff
	   ldr r1, =GPJ0DAT
	   str r0, [r1]   
	 
	   ldr r0, = (1<<1)
	   ldr r1, =GPD0DAT
	   str r0, [r1]
	   bl _delay
	   
	   //LED4��
	   ldr r0, = ~(1<<1)
	   ldr r1, =GPD0DAT
	   str r0, [r1]
	   bl _delay
	   
	   ldr r0, = (1<<1)
	   ldr r1, =GPD0DAT
	   str r0, [r1]	   
	   
	   //LED3��
	   ldr r0, = ~(1<<5)
	   ldr r1, =GPJ0DAT
	   str r0, [r1]
	   bl _delay
	   
	   //LED2��,ͬʱLED3��
	   ldr r0, = ~(1<<4)
	   ldr r1, =GPJ0DAT
	   str r0, [r1]
	   bl _delay
	   
	   //LED1��
	   ldr r0, = ~(1<<3)
	   ldr r1, =GPJ0DAT
	   str r0, [r1]
	   bl _delay
	   
	   //ȫ��
	   ldr r0, = 0x00
	   ldr r1, =GPJ0DAT
	   str r0, [r1]
	   
	   ldr r0, = ~(1<<1)
	   ldr r1, =GPD0DAT
	   str r0, [r1]
	   
	   bl _delay
	   
	   b flash
	   
	   
	b .                           // .����ǰ��һ��ָ��ĵ�ַ��Ҳ����ѭ��      
//flag:                            
//     b flag                       //д��һ����ѭ������Ϊ���������ֱ����CPU�����еģ�
                                  //CPU�����������������ֱ��CPU�ϵ�ػ���������ǵĳ������еĴ��붼ִ������
								  //CPU�ͻ��ܷ��ܷ��Ժ���δ����ģ�����ǧ������CPU�ܷɣ���
   							      //����CPU�ܷɵİ취������������������ִ����������ѭ��
								  //b Ϊ��תָ�ԭ�ش�ת
								
								
_delay:
	  ldr r2, =20000000
	  ldr r3, =0x0
delay_loop:
      sub r2,r2, #1
	  cmp r2, r3                  //r2=r3,��Z��־λ=1�� ��һ��eq�ͻ����
	  bne delay_loop
	  mov pc, lr                  //��������
	  
	  
#endif