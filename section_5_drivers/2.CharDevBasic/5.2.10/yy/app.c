#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FILE "/dev/test"

int main()
{
	int fd = -1;
	//���ļ�
	fd = open(FILE, O_RDWR);
	if(fd)
	{
		printf("open %s failed...\n",FILE);
	}
	printf("open %s sucess...\n",FILE);
	
	//��д�ļ�
	
	//�ر��ļ�
	close(fd);
	return 0;
}