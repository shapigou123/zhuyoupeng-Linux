#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include <pthread.h>
#include <semaphore.h>

char buf[200];
sem_t sem;
unsigned int flag = 0;

void *func (void *arg)
{
	sem_wait(&sem);
	while (flag == 0)
	{
		
		printf("本次输入了%d个字符\n", strlen(buf));
		memset(buf, 0, sizeof(buf));
		sem_wait(&sem);
	}	
	pthread_exit(NULL);
}
int main(void)
{
	// 思路就是创建子进程，然后父子进程中分别进行读键盘和鼠标的工作
	pthread_t thread = -1;

	int fd = -1;
	int ret = -1;
	
	 sem_init(&sem, 0, 0);  //pshared不为０时此信号量在进程间共享，否则只能为当前进程的所有线程共享；
                            //value为信号量的初始值。　
							
	ret = pthread_create(&thread, NULL, func, NULL);  //线程属性 ；线程传参
	if (ret != 0)
	{
		printf("pthread_create error.\n");
		exit(-1);
	}
	
	
	printf("输入一个字符串，以回车结束\n");	
	
	while(scanf("%s", buf))  //scanf 返回输入的个数
	{
		// 去比较用户输入的是不是end，如果是则退出，如果不是则继续	
		if(!strncmp(buf, "end", 3))
		{
			printf("程序结束\n");
			sem_post(&sem);
			flag = 1;
			break;
		}
		sem_post(&sem);
	}
	
  	// 回收子线程
	printf("等待回收子线程\n");
	ret = pthread_join(thread, NULL);
	if (ret != 0)
	{
		printf("pthread_join error.\n");
		exit(-1);
	}
	printf("子线程回收成功\n");
	sem_destroy(&sem);
	
	return 0;
	
}