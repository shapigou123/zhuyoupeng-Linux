#include <stdio.h>

int main(void)
{
#if 1
	int a[3] = {0x11223344, 0x55667788, 0};
	
	int *p1 = a;
	printf("*p1 = 0x%x\n", *p1);
	
	char *p2 = (char *)a;
	printf("*p2 = 0x%x\n", *p2);
	printf("*p2 = 0x%x\n", *(p2+1));
	printf("*p2 = 0x%x\n", *(p2+2));
	printf("*p2 = 0x%x\n", *(p2+3));
	printf("*p2 = 0x%x\n", *(p2+4));
	printf("*p2 = 0x%x\n", *(p2+5));
#endif	
	
#if 0
	int a = 66666;
	char *p1 = &a;
	printf("*p1 = %d.\n", *p1);//int��ʽȥ����char 
	
	short *p2 = &a;
	printf("*p2 = %d.\n", *p2); //�����1130=66666-65536
#endif	
	
#if 0
	int a = 5;
	int *p1 = &a;
	float *p;
	p = (float *)p1;
	
	printf("*p1 = %d.\n", *p1);
	printf("*p = %f.\n", *p); //����floatȥ����int ����
#endif	
	
#if 0
	int a = 5;
	
	printf("a = %d.\n", a);		// 5
	printf("a = %f.\n", a);		// һ������������֣�һ����֪��������
#endif	
	return 0;
}
















