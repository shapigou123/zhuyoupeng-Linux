#include <stdio.h>
 #include <stdio.h>
 #include <sys/socket.h>
 #include <arpa/inet.h>
 
 
 #define SERPORT   9003
 #define SERADDR    "192.168.10.20"
 
int main(void)
{
	//��һ�� socket 
	 int sockfd = -1;  //socket
	 int ret = -1; 
	 struct sockaddr_in seraddr = {0};  
	 
//	 struct sockaddr_in cliaddr = {0};
//	 socklen_t len = 0;
	 sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == -1)
	{
		perror("socket error");  //Ҫ��errno ����perror
		return -1;
	}
	 printf("the sockfd = %d.\n",sockfd);
	
	// ��2����connect���ӷ�����.׼����������ip��ַ
	seraddr.sin_family = AF_INET;		// ���õ�ַ��ΪIPv4
	seraddr.sin_port = htons(SERPORT);	// ���õ�ַ�Ķ˿ں���Ϣ
	seraddr.sin_addr.s_addr = inet_addr(SERADDR);	//������IP��ַ
	ret = connect(sockfd, (const struct sockaddr *)&seraddr, sizeof(seraddr));
	
	if (ret < 0)
	{
		perror("listen");
		return -1;
	}
	printf("connect success\n");
	
	return 0;
}