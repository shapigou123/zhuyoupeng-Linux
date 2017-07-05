#include <stdio.h>
#include <linux/input.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define DEVICE_KEY		"/dev/input/event1"
#define DEVICE_MOUSE    "/dev/input/event3"

int main(void)
{
	int fd = -1, ret = -1;
	struct input_event ev;
	//��һ�������豸�ļ�
	//fd = open(DEVICE_KEY, O_RDONLY);
	fd = open(DEVICE_MOUSE, O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return -1;
	}
	
	while (1)
	{
		memset(&ev, 0, sizeof(struct input_event));
	
		ret = read(fd, &ev, sizeof(struct input_event));
	
		if(ret != sizeof(struct input_event))
		{
			perror("read");
			close(fd);
			return -1;
		}
		printf("%s.\n",(unsigned char *)&ev);
	}
	close(fd);

	return 0;
	
	
}