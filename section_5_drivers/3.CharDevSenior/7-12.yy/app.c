#include <stdio.h>
#include <sys/stat.h>
//#include <sys/types.h>
#include <fcntl.h>
#include <string.h>

#define FILE "/dev/test"			// 刚才mknod创建的设备文件名

char buf[100];

int main(void)
{
	int i = 0;
	int fd = -1;
	fd = open(FILE, O_RDWR);
	if(fd < 0)
	{
		printf("open %s fail.\n", FILE);
		return -1;
	}
	printf("open %s success.\n",FILE);
	
	
	//读写文件
	//write(fd, "hello world", 11);
	//read(fd, buf, 100);
//	printf("读出来的内容是：%s.\n", buf);
	//关闭文件
	while(1)
	{
		memset(buf, 0, sizeof(buf));
		printf("please input on | off | | flash | break \n");
		scanf("%s",buf);
		if(!strcmp(buf, "on"))
		{
			write(fd, "1", 1);
		}
	
		else if(!strcmp(buf, "off"))
		{
			write(fd, "0", 1);
		}
	
		else if(!strcmp(buf, "flash"))
		{
			for(i=0; i<3;i++)
			{
			write(fd, "1", 1);
			sleep(1);
			write(fd, "0", 1);
			sleep(1);
			}		
		}	
		
		else if(!strcmp(buf, "break"))
		{
			break;
		}
	}
	
	close(fd);
	return 0;
}