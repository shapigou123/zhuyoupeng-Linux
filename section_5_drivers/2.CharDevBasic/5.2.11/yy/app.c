#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FILE "/dev/test"
static char buf[100];
int main()
{
	int fd = -1;
	//打开文件
	fd = open(FILE, O_RDWR);
	if(fd < 0)
	{
		printf("open %s failed...\n",FILE);
	}
	printf("open %s sucess...\n",FILE);
	
	//读写文件
	write(fd,"HELLO WORLD",11);
	read(fd,buf,100);
	
	//关闭文件
	close(fd);
	return 0;
}