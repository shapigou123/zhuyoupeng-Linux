#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
	int fd = -1;
	int pid = -1;
	
	//首先打开一个文件
	fd = open("yy.txt",O_RDWR | O_TRUNC);
	
	if(fd < 0 )
	{
		perror("open");
		return -1;
	}
	
	pid = fork();
	
	if(pid > 0)
	{
		printf("parent\n");
		write(fd, "hello ",6);
        sleep(1);  //等待一秒 让其执行子进程
	}
	else if(pid == 0)
	{
		printf("child\n");
		write(fd, "world ",6);
        sleep(1); //等待一秒 让其执行父进程
	}
	else
	{
		perror("fork");
		return -1;
	}
	close(fd);
	return 0;
		
	
}