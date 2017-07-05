#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>



int main(void)
{
	pid_t ret = -1;
	int fd = -1;
	char buf[200];
	
	ret = fork();
	if (ret == 0)
	{
		fd = open("/dev/input/mouse1", O_RDONLY);
		if (fd < 0)
		{
			perror("open:");
			return -1;
		}
		while(1)
		{   
			sleep(0.5);
			memset(buf, 0, sizeof(buf));
			printf("read MOUSE.\n");
			read(fd, buf, 50);
			printf("鼠标读出的内容是:[%s]\n",buf);
		}
	
	}
	
	else if(ret > 0)
	{
		while(1)
		{
			sleep(0.5);
			memset(buf, 0, sizeof(buf));
			printf("read KEY.\n");
			read(0, buf, 50);
			printf("键盘读出的内容是:[%s]\n",buf);
		}
	
	
	}
	else
	{
		perror("fork:");
	}
	
	return 0;
}