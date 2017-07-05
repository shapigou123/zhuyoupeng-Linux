#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>

#define FBDEVICE "/dev/fb0"
#define WHITE		0xffffffff
#define RED			0xffff0000
#define GREEN		0xff00ff00
#define BLUE		0xff0000ff


#define WIDTH 		1024
#define HEIGHT		600

unsigned int *pfb = NULL;

void draw_back(unsigned int width, unsigned int height, unsigned int color);

int main()
{
	struct fb_var_screeninfo vinfo = {0};
	struct fb_fix_screeninfo finfo = {0};
	
	int fd = -1,ret = -1;
	// 第1步：打开设备
	fd = open(FBDEVICE, O_RDWR);
	if (fd < 0)
	{
		perror("open");
		return -1;
	}
	printf("open %s success.\n", FBDEVICE);
	
	// 第2步：获取设备的硬件信息
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
	
	// 第3步：进行mmap
	pfb = mmap(NULL, finfo.smem_len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if(NULL == pfb)
	{
		perror("mmap");
		return 1;
	}		
	printf("pfb = %p\n", pfb);
	
	draw_back(WIDTH, HEIGHT, GREEN);
	
	close(fd);
	return 0;
}

void draw_back(unsigned int width, unsigned int height, unsigned int color)
{
	unsigned int x, y;
	for(y = 0; y < height; y++)
	{
		for(x = 0; x < width; x++)
		{
			*(pfb + y * WIDTH + x) = color;	
		}
	}
}




















