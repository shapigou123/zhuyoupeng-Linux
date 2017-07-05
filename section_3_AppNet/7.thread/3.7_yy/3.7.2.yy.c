#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
char buf[200];
void *func (void *arg)
{
	while (1)
	{
		memset(buf, 0, sizeof(buf));
		printf("read KEY.\n");
		read(0, buf, 50);
		printf("读出键盘的内容是：[%s].\n", buf);			
	}	
	
}
int main(void)
{
	// 思路就是创建子进程，然后父子进程中分别进行读键盘和鼠标的工作
	pthread_t thread = -1;

	int fd = -1;
	int ret = -1;
	ret = pthread_create(&thread, NULL, func, NULL);  //线程属性 ；线程传参
	if (ret != 0)
	{
		printf("pthread_create error.\n");
		return -1;
	}
		
	// 主任务
	fd = open("/dev/input/mouse1", O_RDONLY);
	if (fd < 0)
	{
		perror("open:");
		return -1;
	}
		
	while (1)
	{
		memset(buf, 0, sizeof(buf));
		printf("before read.\n");
		read(fd, buf, 50);
		printf("读出鼠标的内容是：[%s].\n", buf);
	}	
	
	
	return 0;
	
}