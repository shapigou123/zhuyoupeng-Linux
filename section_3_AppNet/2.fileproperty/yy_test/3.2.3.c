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
	printf("blksize = %d\n\n",buf.st_blksize);
	
	int result_REG = S_ISREG(buf.st_mode);
	int result_DIR = S_ISDIR(buf.st_mode);
	printf("result_is_reg = %d\n",result_REG);
	printf("result_is_dir = %d\n\n",result_DIR);
	
	int read_limited = (buf.st_mode & S_IRUSR) >> 8;
	int write_limited = (buf.st_mode & S_IWUSR) >> 7;
	int exe_limited = (buf.st_mode & S_IXUSR) >> 6;
	//int result = ((buf.st_mode & S_IRUSR)? 1: 0);
	printf("owner has read permission: %d.\n", read_limited);
	printf("owner has write permission: %d.\n", write_limited);
	printf("owner has execute permission: %d.\n", exe_limited);
	
	
	
	return 0;
}