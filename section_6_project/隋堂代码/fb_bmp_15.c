//本文件用来解析BMP图片，并且显示到fb中
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>


#include "bmp.h"
//规定最大支持1920*1080的图片 bpp最多24
#define BMP_MAX_RESOLUTION		(1920*1080)
#define BMP_BUF_SIZE			(BMP_MAX_RESOLUTION*3)
unsigned char bmp_buf[BMP_BUF_SIZE];


//判断一个图片是否为合法的bmp文件
//返回值:如果是则返回0,不是则返回-1
int is_bmp(const char *path)
{
	int fd = -1;
	ssize_t ret = 0;
	char buf[2] = {0};
	//第一步打开图片
	fd = open(path, O_RDONLY);
	if(fd < 0)
	{
		printf("open %s failed\n",path);
		return -1;
	}
	
	//第二步读取头信息
	ret = read(fd, buf, 2);
	if(ret != 2)
	{
		printf("read %s failed",path);
		ret = -1;
		goto close;
	}
	
	//第三步解析头信息
	if((buf[0] == 'B') && (buf[1] == 'M'))
	{
		printf("the %s file  is  a real bmp picture\n", path);
		ret = 0;
	}		
	else
	{
		printf("the %s file  is not a bmp picture\n", path);
		ret = -1;
		goto close;
	}
		
close:	
	close(fd);
	return ret;
		
	}



//参数列表:path:要解析的bmp图片的pathname
//函数功能:该函数解析path这个bmp图片，并且将解析出来的图片数据丢到bmp_buf中去
//返回值:错误时返回-1；正确返回0
int bmp_analyze(const char *path)
{
	int fd = -1;
	unsigned long int len = -1;
	off_t ret = -1;
    BitMapFileHeader fHeader;
	BitMapInfoHeader info;
	unsigned tmp;
	//第一步打开图片
	fd = open(path, O_RDONLY);
	if(fd < 0)
	{
		printf("open %s failed\n",path);
		return -1;
	}

	//第二步读取头信息
	read(fd, &tmp, 2); //文件内部维护了一个文件指针，读了2个字指针后，文件指针往后移动了两个指针。
	read(fd, &fHeader, sizeof(fHeader));	
	printf("bfSize =  %ld. \n",fHeader.bfSize);
	printf("bfOffBits = %ld. \n",fHeader.bfOffBits);

	//第三步读取图片信息
	read(fd, &info, sizeof(info));
	printf("biWidth =  %ld. \n",info.biWidth);
	printf("biHeight =  %ld. \n",info.biHeight);
	printf("picture bpp =  %u. \n",info.biBitCount);

	//第四步读取图片数据
	len = (info.biWidth*info.biHeight*info.biBitCount)/3;
	ret = lseek(fd, fHeader.bfOffBits, SEEK_SET);
	if(ret < 0)
	{
		printf("lseek error\n");
	}
	printf("lseek postion: %d.\n",ret);

	read(fd, bmp_buf, len);
	
	//显示图片内容
	fb_draw(bmp_buf);
	close(fd);
	return 0;
	
}
















