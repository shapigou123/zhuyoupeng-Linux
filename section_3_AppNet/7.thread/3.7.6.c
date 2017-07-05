#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>



char buf[200] = {0};
pthread_mutex_t mutex;
unsigned int flag = 0;


// 子线程程序，作用是统计buf中的字符个数并打印
void *func(void *arg)
{
	// 子线程首先应该有个循环
	// 循环中阻塞在等待主线程激活的时候，子线程被激活后就去获取buf中的字符
	// 长度，然后打印；完成后再次被阻塞
	
	//while (strncmp(buf, "end", 3) != 0)
	sleep(1); //（一）确保主线程先被执行。及时子线程先被调度，则在这里会睡眠，主线程先运行有意义代码
	while (flag == 0)
	{	
		pthread_mutex_lock(&mutex); //锁没人用就自己上锁，然后就可以执行下面的代码了
		printf("本次输入了%d个字符\n", strlen(buf));
		memset(buf, 0, sizeof(buf));
		pthread_mutex_unlock(&mutex);
		sleep(1);
		//子线程解锁成功后如果不睡眠，那么下次上锁的还是子线程，又会出现很多重复的pr"本次输入了%d个字符\n"
	}
	
	
	pthread_exit(NULL);
}


int main(void)
{
	int ret = -1;
	pthread_t th = -1;
	
	
	
	pthread_mutex_init(&mutex, NULL);
	
	ret = pthread_create(&th, NULL, func, NULL);
	if (ret != 0)
	{
		printf("pthread_create error.\n");
		exit(-1);
	}
	
	printf("输入一个字符串，以回车结束\n");
	while (1)
	{
		pthread_mutex_lock(&mutex);
		scanf("%s", buf);
		pthread_mutex_unlock(&mutex);
		// 去比较用户输入的是不是end，如果是则退出，如果不是则继续		
		if (!strncmp(buf, "end", 3))
		{
			printf("程序结束\n");
			flag = 1;
			
			//exit(0);
			break;
		}
		sleep(1); //（二）保证主线程scanf之后会解锁，解锁完后会进入睡眠；然后把主动权交给子线程。子线程肯定能上锁成功。
		// 主线程在收到用户收入的字符串，并且确认不是end后
		// 就去发信号激活子线程来计数。
		// 子线程被阻塞，主线程可以激活，这就是线程的同步问题。
		// 信号量就可以用来实现这个线程同步
	}

	
	// 回收子线程
	printf("等待回收子线程\n");
	ret = pthread_join(th, NULL);
	if (ret != 0)
	{
		printf("pthread_join error.\n");
		exit(-1);
	}
	printf("子线程回收成功\n");
	
	pthread_mutex_destroy(&mutex);
	
	return 0;
}



