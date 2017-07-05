#include <stdio.h>
#include <unistd.h>			// unix standand
#include <signal.h>



void func(int sig)
{
	#if 1
	if (sig == SIGALRM)
	{
		printf("alarm happened.\n");
	}
	#endif
}

void mysleep(unsigned int seconds);


int main(void)
{
	//printf("before mysleep.\n");
	//mysleep(3);
	//printf("after mysleep.\n");
	
#if 1
	unsigned int ret = -1;

//signal(SIGALRM, func);
/*********************************************/
	
	struct sigaction act = {0};
	act.sa_handler = func;
	sigaction(SIGALRM, &act, NULL);
	
	
	ret = alarm(5);
	printf("1st, ret = %d.\n", ret);

	sleep(3);
	
	ret = alarm(5);		// 返回值是2但是本次alarm会重新定5s
	printf("2st, ret = %d.\n", ret);
	
	sleep(1);
	
	ret = alarm(5);
	printf("3st, ret = %d.\n", ret);
	
	
	
	
	//while (1);
	pause();		

#endif	
	return 0;
}

void mysleep(unsigned int seconds)
{
	struct sigaction act = {0};
	//act.sa_handler = SIG_DFL;
	act.sa_handler = func;
	sigaction(SIGALRM, &act, NULL);  //给一个空函数func；设置新的捕获函数
	alarm(seconds);
	pause();
}



