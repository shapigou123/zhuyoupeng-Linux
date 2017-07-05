#include<stdio.h>
#include <string.h>
#include <stdlib.h>

#define FILENAME  "test.txt"
int main(void)
{
	char buf[] = {"hello my world"};
    size_t len = -1;
	FILE *fp = NULL;
	
	fp = fopen(FILENAME, "r+");
	//fp = fopen(FILENAME, "w+");
	if( NULL == fp)
	{
		perror("fopen");
		exit(-1);
	}
	printf("fopen success. fp = %p.\n", fp);


#if 0
   // memset(buf, 0, sizeof(buf));
	len = fwrite(buf, 1, sizeof(buf)/sizeof(char), fp);
	printf("the len is %d\n",len);
	printf("[%s]\n",buf);
#endif	

	//╤анд╪Ч
#if 1
	memset(buf, 0, sizeof(buf));
	len = fread(buf, 1, 20, fp);
	printf("the len is %d\n",len);
	printf("[%s]\n",buf);
#endif
	
	fclose(fp);
	return 0;
	
	
}