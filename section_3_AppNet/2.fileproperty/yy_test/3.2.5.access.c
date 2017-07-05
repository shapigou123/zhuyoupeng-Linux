#include <unistd.h>
#include <stdio.h>

#define NAME "1.txt"
int main(void)
{
	int ret = -1;
	ret = access(NAME,F_OK);
	
	if(ret < 0)
	{
     	printf("the file does not exist\n");
		return -1;
	}
	else
	{
		printf("the file exist\n");
	}
	
	
	ret = access(NAME,W_OK);
	if(ret < 0)
	{
     	printf("the file have no permissions to write \n");
		//return -1;
	}
	else
	{
		printf("the file grants writs permissions\n");
	}
	
	
	ret = access(NAME,R_OK);
	if(ret < 0)
	{
     	printf("the file have no permissions to read\n");
		//return -1;
	}
	else
	{
		printf("the file grants read permissions\n");
	}
	
	 return 0;
	 
	
}
