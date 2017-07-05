#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

typedef void (*sighandler_t)(int);


void func(int sig)
{
	if (SIGINT != sig)
		return;
	
	printf("func for signal: %d.\n", sig);
}


int main(void)
{
	sighandler_t ret = ((sighandler_t)-2);
	signal(SIGINT, func);
	//signal(SIGINT, SIG_DFL);		// 指定信号SIGINT为默认处理#
	//signal(SIGINT, SIG_IGN);
	
	
#if 0
    ret = signal(SIGINT, SIG_IGN);		// 指定信号SIGINT为忽略处理
	if (SIG_ERR == ret)
	{
		perror("signal:");
		exit(-1);
	}
#endif	
	printf("before while(1)\n");
	//while(1);
	pause();
	printf("after while(1)\n");
	
	return 0;
}