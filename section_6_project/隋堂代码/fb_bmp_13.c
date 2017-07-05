//本文件用来解析BMP图片，并且显示到fb中
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>


//规定最大支持1920*1080的图片 bpp最多24
#define BMP_MAX_RESOLUTION		(1920*1080)
#define BMP_BUF_SIZE			(BMP_MAX_RESOLUTION*3)
unsigned char bmp_buf[BMP_BUF_SIZE];



//参数列表:path:要解析的bmp图片的pathname
//函数功能:该函数解析path这个bmp图片，并且将解析出来的图片数据丢到bmp_buf中去
//返回值:错误时返回-1；正确返回0
int bmp_analyze(const char *path)
{
	int fd = -1;
	ssize_t ret = 0;
	char buf[54] = {0};
	//第一步打开图片
	fd = open(path, O_RDONLY);
	if(fd < 0)
	{
		printf("open %s failed\n",path);
	}

	//第二步读取头信息
	ret = read(fd, buf, 54);
	if(ret != 54)
	{
		printf("read %s failed",path);
	}

	if((buf[0] == 'B') && (buf[1] == 'M'))
	{
		printf("the %s file  is  a real bmp picture\n", path);
	}
	
	else
	{
		printf("the %s file  is not a bmp picture\n", path);
	}
	
	//解析头信息
	printf("the width resolution is %d. \n",*(unsigned int *)(buf+0x12));
	printf("the height resolution is %d. \n",*(unsigned int *)(buf+0x16));

	close(fd);
	return 0;
	
}



