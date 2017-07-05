#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define FILE "/dev/test"
static char buf[100];
int main()
{
	int fd = -1;
	int i = 0;
	//打开文件
	fd = open(FILE, O_RDWR);
	if(fd < 0)
	{
		printf("open %s failed...\n",FILE);
		return -1;
	}
	printf("open %s sucess...\n",FILE);
	
	//读写文件
#if 0
	write(fd, "on", 2);
	sleep(3);
	write(fd, "off", 3);
	sleep(2);	
	write(fd, "on", 2);
	sleep(1);
	write(fd, "off", 3);
#endif

#if 0	
	write(fd, "1", 1);
	sleep(3);
	write(fd, "0", 1);
	sleep(2);	
	write(fd, "1", 1);
	//sleep(1);
	//write(fd, "0", 3);
#endif
	while(1)
	{
		memset(buf, 0, sizeof(buf));
		printf("请输入 on | off |flash \n");
		scanf("%s", buf);
		
		if(!strcmp(buf, "on"))
			write(fd, "1", 1);
		
		else if(!strcmp(buf, "off"))
			write(fd, "0", 1);
		
		else if(!strcmp(buf, "flash"))
		{
			for(i; i<3; i++)
			{
			    write(fd, "1", 1);
				sleep(1);
				write(fd, "0", 1);	
				sleep(1);
			}
		}
		
		else if(!strcmp(buf, "quit"))
			break;
	}
	//关闭文件
	close(fd);
	return 0;
}