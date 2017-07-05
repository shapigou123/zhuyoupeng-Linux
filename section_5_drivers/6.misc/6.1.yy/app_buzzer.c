#include <stdio.h>
#include <stropts.h>
#include <sys/stat.h>
#include <fcntl.h>

#define DEVICE_NAME     "/dev/buzzer"

#define PWM_IOCTL_SET_FREQ		1
#define PWM_IOCTL_STOP			0

int main()
{
	int fd = -1;
	fd = open(DEVICE_NAME, O_RDWR);
	if(fd < 0)
	{
		perror("fopen failed...\n");
		return -1;
	}
	ioctl(fd, PWM_IOCTL_SET_FREQ, 10000);
	sleep(3);
	ioctl(fd, PWM_IOCTL_STOP);
	sleep(3);
	ioctl(fd, PWM_IOCTL_SET_FREQ, 1000);
	sleep(3);
	ioctl(fd, PWM_IOCTL_STOP);
	close(fd);
	
	return 0;
}