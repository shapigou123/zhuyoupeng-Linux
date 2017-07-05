#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MYADD   "192.168.1.103"
int main(void)
{
#if 0 
// inet_pton
	int ret = 0;
	struct in_addr addr = {0};  //用封装的该结构体存储32位二进制，
	ret = inet_pton(AF_INET, MYADD, &addr);
	if(ret != 1)
	{
		perror("inet_pton error");
		return -1;
	}
	printf("the address is 0x%x\n",addr.s_addr);
#endif


#if 0

//inet_addr
	in_addr_t ret = 0;
	
	ret = inet_addr(MYADD);
	if(ret == INADDR_NONE)
	{
		printf("inet_addr error");
		return -1;
	}
    printf("0x%x\n",ret);
 
#endif 

#if 1
	const char *ret = NULL;
	in_addr_t addr = 0x6703a8c1;   //下面两条语句也可以
	//struct in_addr addr = {0}; 
	//addr.s_addr = 0x6703a8c1;
	
	char buf[50] = {0};
	ret = inet_ntop(AF_INET, &addr, buf, sizeof(buf));
		if (ret == NULL)
	{
		printf("inet_ntop error\n");
		return -1;
	}

	printf("ip addr = %s.\n", buf);
	
	


#endif

	return 0;
	
}