#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/fb.h>

#define FBDEVICE "/dev/fb0"

int main()
{
	struct fb_var_screeninfo vinfo = {0};
	struct fb_fix_screeninfo finfo = {0};
	
	int fd = -1,ret = -1;
	// ��1�������豸
	fd = open(FBDEVICE, O_RDWR);
	if (fd < 0)
	{
		perror("open");
		return -1;
	}
	printf("open %s success.\n", FBDEVICE);
	
	// ��2������ȡ�豸��Ӳ����Ϣ
	ret = ioctl(fd, FBIOGET_FSCREENINFO, &finfo);
	if(ret < 0)
	{
		perror("ioctl");
		close(fd);
		return -1;
	}
	printf("smem_start = 0x%x , smem_len = %u\n", finfo.smem_start,finfo.smem_len);
	
	ret = ioctl(fd, FBIOGET_VSCREENINFO, &vinfo);	
	if(ret < 0)
	{
		perror("ioctl");
		close(fd);
		return -1;
	}
	printf("xres = %d , yres = %d\n", vinfo.xres,vinfo.yres);
	printf("xres_virtual = %d , yres_virtual = %d\n", vinfo.xres_virtual,vinfo.yres_virtual);
	printf("bits_per_pixel = %d\n", vinfo.bits_per_pixel);
	
	// ��3��������mmap
	close(fd);
	return 0;
}

