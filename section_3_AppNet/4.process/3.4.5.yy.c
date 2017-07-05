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
	
	//���ȴ�һ���ļ�
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
        sleep(1);  //�ȴ�һ�� ����ִ���ӽ���
	}
	else if(pid == 0)
	{
		printf("child\n");
		write(fd, "world ",6);
        sleep(1); //�ȴ�һ�� ����ִ�и�����
	}
	else
	{
		perror("fork");
		return -1;
	}
	close(fd);
	return 0;
		
	
}