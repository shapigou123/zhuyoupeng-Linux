#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#if 1
int main(void)
{
	// 读取鼠标
	int fd = -1;
	char buf[200];
	
	fd = open("/dev/input/mouse1", O_RDONLY);  //鼠标设备的设备文件
	if (fd < 0)
	{
		perror("open:");
		return -1;
	}
	
	memset(buf, 0, sizeof(buf));
	printf("鼠标 read.\n");
	read(fd, buf, 50);
	printf("鼠标读出的内容是：[%s].\n", buf);
	
	
	// 读键盘
	memset(buf, 0, sizeof(buf));
	printf("键盘 read.\n");
	read(0, buf, 5);
	printf("键盘读出的内容是：[%s].\n", buf);
	
	
	return 0;
}
#endif

#if 0
int main(void)
{
	// 读取鼠标
	int fd = -1;
	char buf[200];
	
	fd = open("/dev/input/mouse0", O_RDONLY);
	if (fd < 0)
	{
		perror("open:");
		return -1;
	}
	
	memset(buf, 0, sizeof(buf));
	printf("before read.\n");
	read(fd, buf, 50);
	printf("读出的内容是：[%s].\n", buf);
	
	
	return 0;
}
#endif


#if 0
int main(void)
{
	// 读取键盘
	// 键盘就是标准输入，stdin
	
	char buf[100];
	
	memset(buf, 0, sizeof(buf));
	printf("before read.\n");
	read(0, buf, 5);  //fd = 0；
	printf("读出的内容是：[%s].\n", buf);
	
	return 0;
}
#endif