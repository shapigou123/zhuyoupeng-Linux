#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <poll.h>



int main(void)
{
	// 读取鼠标
	int fd = -1, ret = -1;
    int flag = -1;
	char buf[200];
	struct pollfd myfds[2] = {0};  //要定义成数组，因为数组有自己的内存空间，而原型中传参是指针，没有内存空间。 再整体初始化为0
	
	//fd = open("/dev/input/mouse0", O_RDONLY | O_NONBLOCK);
	fd = open("/dev/input/mouse0", O_RDONLY );
	if (fd < 0)
	{
		perror("open:");
		return -1;
	}
/******************************************************/	
#if 0
	// 把0号文件描述符（stdin）变成非阻塞式的
	flag = fcntl(0, F_GETFL);		// 先获取原来的flag
	flag |= O_NONBLOCK;				// 添加非阻塞属性
	fcntl(0, F_SETFL, flag);		// 更新flag
	// 这3步之后，0就变成了非阻塞式的了
#endif	
	
/******************************************************/
	
	// 初始化我们的pollfd
	myfds[0].fd = 0;			// 键盘
	myfds[0].events = POLLIN;	// 等待读操作
	
	myfds[1].fd = fd;			// 鼠标
	myfds[1].events = POLLIN;	// 等待读操作，文件描述符fd上感兴趣的事件

	ret = poll(myfds, fd+1, 5000);  //myfds不用加取地址符号，因为它是数组名
	if (ret < 0)
	{
		perror("poll: ");
		return -1;
	}
	else if (ret == 0)
	{
		printf("超时了\n");
	}
	else
	{
		// 等到了一路IO，然后去监测到底是哪个IO到了，处理之。revents文件描述符fd上当前实际发生的事件*
		if (myfds[0].events == myfds[0].revents)
		{
			// 这里处理键盘
			memset(buf, 0, sizeof(buf));
			read(0, buf, 5);
			printf("键盘读出的内容是：[%s].\n", buf);
		}
		
		if (myfds[1].events == myfds[1].revents)
		{
			// 这里处理鼠标
			memset(buf, 0, sizeof(buf));
			read(fd, buf, 50);
			printf("鼠标读出的内容是：[%s].\n", buf);
		}

	}

	return 0;
}




