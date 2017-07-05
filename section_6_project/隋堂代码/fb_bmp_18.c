//���ļ���������BMPͼƬ��������ʾ��fb��
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>


#include "bmp.h"
#include <fb.h>
#include <config.h>
//�涨���֧��1920*1080��ͼƬ bpp���24
#define BMP_MAX_RESOLUTION		(1920*1080)
#define BMP_BUF_SIZE			(BMP_MAX_RESOLUTION*3)
unsigned char bmp_buf[BMP_BUF_SIZE];


//�ж�һ��ͼƬ�Ƿ�Ϊ�Ϸ���bmp�ļ�
//����ֵ:������򷵻�0,�����򷵻�-1
int is_bmp(struct pic_info *pPic)
{
	int fd = -1;
	ssize_t ret = 0;
	char buf[2] = {0};
	//��һ����ͼƬ
	fd = open(pPic->pathname, O_RDONLY);
	if(fd < 0)
	{
		debug("open %s failed\n",pPic->pathname);
		return -1;
	}
	
	//�ڶ�����ȡͷ��Ϣ
	ret = read(fd, buf, 2);
	if(ret != 2)
	{
		debug("read %s failed",pPic->pathname);
		ret = -1;
		goto close;
	}
	
	//����������ͷ��Ϣ
	if((buf[0] == 'B') && (buf[1] == 'M'))
	{
		debug("the %s file  is  a real bmp picture\n", pPic->pathname);
		ret = 0;
	}		
	else
	{
		debug("the %s file  is not a bmp picture\n", pPic->pathname);
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
int bmp_analyze(struct pic_info *pPic)
{
	int fd = -1;
	unsigned long int len = -1;
	int ret = -1;
    BitMapFileHeader fHeader;
	BitMapInfoHeader info;
	unsigned tmp;
	//��һ����ͼƬ
	fd = open(pPic->pathname, O_RDONLY);
	if(fd < 0)
	{
		debug("open %s failed\n", pPic->pathname);
		return -1;
	}

	//�ڶ�����ȡͷ��Ϣ
	read(fd, &tmp, 2); //�ļ��ڲ�ά����һ���ļ�ָ�룬����2����ָ����ļ�ָ�������ƶ�������ָ�롣
	read(fd, &fHeader, sizeof(fHeader));	
	debug("bfSize =  %ld. \n",fHeader.bfSize);
	debug("bfOffBits = %ld. \n",fHeader.bfOffBits);

	//��������ȡͼƬ��Ϣ
	read(fd, &info, sizeof(info));
	debug("biWidth =  %ld. \n",info.biWidth);
	debug("biHeight =  %ld. \n",info.biHeight);
	debug("picture bpp =  %u. \n",info.biBitCount);
	
	//�����ݷ��������Լ�����Ľṹ����
	pPic->width = info.biWidth;
	pPic->height = info.biHeight;
	pPic->bpp = info.biBitCount;
	//���Ĳ���ȡͼƬ����
	len = (info.biWidth*info.biHeight*info.biBitCount)/3;
	ret = lseek(fd, fHeader.bfOffBits, SEEK_SET);
	if(ret < 0)
	{
		debug("lseek error\n");
	}
	debug("lseek postion: %d.\n",ret);

	read(fd, bmp_buf, len);
	pPic->pData = bmp_buf;
	//��ʾͼƬ����
	fb_draw(pPic);
	close(fd);
	return 0;
	
}
















