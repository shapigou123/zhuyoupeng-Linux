//���ļ���������BMPͼƬ��������ʾ��fb��
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>


#include "bmp.h"
//�涨���֧��1920*1080��ͼƬ bpp���24
#define BMP_MAX_RESOLUTION		(1920*1080)
#define BMP_BUF_SIZE			(BMP_MAX_RESOLUTION*3)
unsigned char bmp_buf[BMP_BUF_SIZE];


//�ж�һ��ͼƬ�Ƿ�Ϊ�Ϸ���bmp�ļ�
//����ֵ:������򷵻�0,�����򷵻�-1
int is_bmp(const char *path)
{
	int fd = -1;
	ssize_t ret = 0;
	char buf[2] = {0};
	//��һ����ͼƬ
	fd = open(path, O_RDONLY);
	if(fd < 0)
	{
		printf("open %s failed\n",path);
		return -1;
	}
	
	//�ڶ�����ȡͷ��Ϣ
	ret = read(fd, buf, 2);
	if(ret != 2)
	{
		printf("read %s failed",path);
		ret = -1;
		goto close;
	}
	
	//����������ͷ��Ϣ
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



//�����б�:path:Ҫ������bmpͼƬ��pathname
//��������:�ú�������path���bmpͼƬ�����ҽ�����������ͼƬ���ݶ���bmp_buf��ȥ
//����ֵ:����ʱ����-1����ȷ����0
int bmp_analyze(const char *path)
{
	int fd = -1;
    BitMapFileHeader fHeader;
	unsigned tmp;
	//��һ����ͼƬ
	fd = open(path, O_RDONLY);
	if(fd < 0)
	{
		printf("open %s failed\n",path);
		return -1;
	}

	//�ڶ�����ȡͷ��Ϣ
	read(fd, &tmp, 2);
	read(fd, &fHeader, sizeof(fHeader));	
	printf("bfSize =  %ld. \n",fHeader.bfSize);
	printf("bfOffBits = %ld. \n",fHeader.bfOffBits);

	close(fd);
	return 0;
	
}
















