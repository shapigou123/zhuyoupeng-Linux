 #include <stdio.h>
 #include <sys/socket.h>
 #include <arpa/inet.h>
 //#include <sys/types.h> 
 #include <string.h>
 #define SERPOERT   9004
 #define SERADDR    "192.168.10.20"
 #define BACKLOG	100
 
 
//char recvbuf[100]; 
 int main(void)
 {
//第一步 socket 
	 int sockfd = -1;  //socket
	 int clifd = -1;
	 int ret = -1;     //bind recv 
	 struct sockaddr_in seraddr = {0};  
	 struct sockaddr_in cliaddr = {0};
	 socklen_t len = 0;
	 
	 char recvbuf[100];
	 sockfd = socket(AF_INET, SOCK_STREAM, 0);
	 
	if(sockfd == -1)
	{
		perror("socket error");  //要有errno 才能perror
		return -1;
	}
	 printf("the sockfd = %d.\n",sockfd);
	 
//第二步 bind绑定ip地址和端口号（服务器的端口号要自己指定）
	 seraddr.sin_family = AF_INET;
	 seraddr.sin_port = htons(SERPOERT);
	 seraddr.sin_addr.s_addr =  inet_addr(SERADDR);             ////设置地址的端口号信息。因为要考虑网络字节序。将当前电脑的字节序转化为网络字节序
	 ret = bind(sockfd, (const struct sockaddr *)&seraddr, sizeof(seraddr));  
	 
	                                        //printf("haha1\n");
											
	 //强制转换兼容ipv4/ipv6； sizeof能辅助认出是IPV4/IPV6
	 if (ret < 0)
	{
		perror("bind");
		return -1;
	}
	printf("bind success.\n");
	
	                                      //printf("haha2\n");
										  
//第三步 listen监听 当前电脑的当前端口号
	ret = listen(sockfd, BACKLOG);	 //执行该语句后，accept阻塞等待客户端来连接服务器
	if (ret < 0)
	{
		perror("perror");
		return -1;
	}
	
	                                     //printf("haha3\n");
										 
//第四步 accept
	clifd = accept(sockfd, (struct sockaddr *)&cliaddr, &len);
	printf("连接已经建立，client fd = %d.\n", clifd);
	
//第五步 服务器接受客户端发来的数据
#if 1
    memset(recvbuf, 0, sizeof(recvbuf));
	ret = recv(clifd, recvbuf, sizeof(recvbuf), 0);
	printf("server成功接收了%d个字节\n", ret);
	printf("server接受的内容是：%s\n", recvbuf);
#endif

#if 1
//第五步 服务器发送客户端接收
    memset(recvbuf, 0, sizeof(recvbuf));
	strcpy(recvbuf, "i love");
	ret = send(clifd, recvbuf, strlen(recvbuf), 0);
	printf("server发送了%d个字符\n", ret);
	printf("server发送的内容是：%s\n",recvbuf);
#endif
	
	return 0;
 }