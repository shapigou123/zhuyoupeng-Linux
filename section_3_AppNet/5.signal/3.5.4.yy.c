#include <stdio.h>
#include <unistd.h>			// unix standand
#include <signal.h>

void func(int sig)
{
	if (sig == SIGALRM)
		printf("alarm happened.\n");
}

int main(void)
{
	unsigned int ret = -1;

	struct sigaction act = {0};
	act.sa_handler = func;
	sigaction(SIGALRM, &act, NULL);
	//signal(SIGALRM, func);
	ret = alarm(3);
	printf("ret = %d.\n",ret);
	//while(1);
	pause();
	return 0;
}