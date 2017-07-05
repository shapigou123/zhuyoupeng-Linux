#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define NAME "1.txt"
int main(void)
{
	int ret = -1;
	struct stat buf;
	
	memset(&buf,0,sizeof(buf));
	ret = stat(NAME,&buf);
	if(ret < -1)
	{
		perror("stat");
		exit(-1);
	}	
	
	printf("inode = %d\n",buf.st_ino);
	printf("size = %d\n",buf.st_size);
	printf("blksize = %d\n",buf.st_blksize);
	return 0;
}