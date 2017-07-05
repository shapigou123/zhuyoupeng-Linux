#include <stdio.h>
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
	
	memset(&buf, 0, sizeof(buf));		// memset后buf中全是0
	ret = stat(NAME, &buf);				// stat后buf中有内容了
	if (ret < 0)
	{
		perror("stat");
		exit(-1);
	}
	
#if 1	
	// 判断这个文件属性
	int result1 = S_ISREG(buf.st_mode);
	//int result = S_ISDIR(buf.st_mode);
	printf("result1 = %d\n", result1);
#endif

	// 文件权限测试
	unsigned int result2 = (buf.st_mode & S_IRWXU) >> 8;
	//unsigned int result2 = ((buf.st_mode & S_IRUSR)? 1: 0);
	printf("file owner: %u.\n", result2);
	
	
	
	
	return 0;
}



















