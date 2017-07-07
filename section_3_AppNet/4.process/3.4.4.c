#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>


int main(void)
{
	pid_t p1 = -1;
	
	p1 = fork();		// 返回2次
	
	if (p1 == 0)
	{
		// 这里一定是子进程执行的代码
		
		// 先sleep一下让父进程先运行，先死
		//sleep(1);
		
		printf("子进程, 子进程ID = %d.\n", getpid());		
	//printf("hello world.\n");
		printf("子进程, 此时父进程死了之后，父进程的ID = %d.\n", getppid());
	}
	
	if (p1 > 0)
	{
		// 这里一定是父进程执行的代码
		printf("父进程, 父进程ID = %d.\n", getpid());
		printf("父进程, 子进程ID = %d.\n", p1);
	}
	
	if (p1 < 0)
	{
		// 这里一定是fork出错了
	}
	
	// 在这里所做的操作，父进程和子进程都会打印出来
	//printf("hello world, pid = %d.\n", getpid());

	return 0;
}