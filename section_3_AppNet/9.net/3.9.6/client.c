#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <arpa/inet.h>


#define SERADDR		"192.168.10.20"		// 服务器开放给我们的IP地址和端口号
#define SERPORT		9003



int main(void)
{
	// 第1步：先socket打开文件描述符
	int sockfd = -1, ret = -1;
	struct sockaddr_in seraddr = {0};
	struct sockaddr_in cliaddr = {0};
	
	// 第1步：socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (-1 == sockfd)  //一定要写错误检测代码，出现错误容易定位
	{
		perror("socket");
		return -1;
	}
	printf("socketfd = %d.\n", sockfd);  //每走一步 能调试就先调试 一定要勤调试
	
	// 第2步：connect链接服务器.准备服务器的ip地址
	seraddr.sin_family = AF_INET;		// 设置地址族为IPv4
	seraddr.sin_port = htons(SERPORT);	// 设置地址的端口号信息
	seraddr.sin_addr.s_addr = inet_addr(SERADDR);	//　设置IP地址
	ret = connect(sockfd, (const struct sockaddr *)&seraddr, sizeof(seraddr));
	if (ret < 0)
	{
		perror("listen");
		return -1;
	}
	printf("connect result, ret = %d.\n", ret);
	
	
	return 0;
}