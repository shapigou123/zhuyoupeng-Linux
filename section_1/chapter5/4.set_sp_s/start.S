/*
 * �ļ�����	led.s	
 * ���ߣ�	����ʦ
 * ������	��ʾ�������ջ���ҵ���C���Գ���������LED
 */

#define WTCON		0xE2700000

#define SVC_STACK	0xd0037d80

.global _start					// ��_start�������Ը�Ϊ�ⲿ�����������ļ��Ϳ��Կ���_start��
_start:
	// ��1�����ؿ��Ź�����WTCON��bit5д��0���ɣ�
	ldr r0, =WTCON
	ldr r1, =0x0
	str r1, [r0]
	
	// ��2��������SVCջ
	ldr sp, =SVC_STACK

	// ������֮��Ϳ��Կ�ʼ����C������
	bl led_blink					// led_blink��C����ʵ�ֵ�һ������
	
// ������������ѭ�����ܶ�
	b .
	

	
	
	

	
	
	
	
	
	
	
	
	