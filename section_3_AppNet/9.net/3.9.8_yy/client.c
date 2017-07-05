#include <stdio.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

 
#define SERPORT    9004
#define SERADDR    "192.168.10.20"

//char sendbuf[100];  


int main(void)
{
//第一步 socket 
	 int sockfd = -1;  //socket
	 int ret = -1; 
	 struct sockaddr_in seraddr = {0};  
	 

    // struct sockaddr_in cliaddr = {0};
    // socklen_t len = 0;
	
	char sendbuf[100];
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == -1)
	{
		perror("socket error");  //要有errno 才能perror
		return -1;
	}
	printf("the sockfd = %d.\n",sockfd);
	
// 第二步：connect链接服务器.准备服务器的ip地址
	seraddr.sin_family = AF_INET;		// 设置地址族为IPv4
	seraddr.sin_port = htons(SERPORT);	// 设置地址的端口号信息
	seraddr.sin_addr.s_addr = inet_addr(SERADDR);	//　设置IP地址
	ret = connect(sockfd, (const struct sockaddr *)&seraddr, sizeof(seraddr));
	
	if (ret < 0)
	{
		perror("listen");
		return -1;
	}
	printf("connect success\n");
	
	

#if 1
	//第三步客户端发送
	memset(sendbuf, 0, sizeof(sendbuf));
	strcpy(sendbuf, "hello world1.");
	ret = send(sockfd, sendbuf, strlen(sendbuf), 0);
	printf("client发送了%d个字符\n", ret);
	printf("client发送的内容是：%s\n",sendbuf);
	
#endif

#if 1
    //第三步客户端接收
	memset(sendbuf, 0, sizeof(sendbuf));
	ret = recv(sockfd, sendbuf, sizeof(sendbuf), 0);
	printf("client成功接收了%d个字节\n", ret);
	printf("client接受的内容是：%s\n", sendbuf);

#endif

return 0;
}