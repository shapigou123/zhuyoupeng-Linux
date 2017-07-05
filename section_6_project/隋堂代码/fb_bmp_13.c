//���ļ���������BMPͼƬ��������ʾ��fb��
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>


//�涨���֧��1920*1080��ͼƬ bpp���24
#define BMP_MAX_RESOLUTION		(1920*1080)
#define BMP_BUF_SIZE			(BMP_MAX_RESOLUTION*3)
unsigned char bmp_buf[BMP_BUF_SIZE];



//�����б�:path:Ҫ������bmpͼƬ��pathname
//��������:�ú�������path���bmpͼƬ�����ҽ�����������ͼƬ���ݶ���bmp_buf��ȥ
//����ֵ:����ʱ����-1����ȷ����0
int bmp_analyze(const char *path)
{
	int fd = -1;
	ssize_t ret = 0;
	char buf[54] = {0};
	//��һ����ͼƬ
	fd = open(path, O_RDONLY);
	if(fd < 0)
	{
		printf("open %s failed\n",path);
	}

	//�ڶ�����ȡͷ��Ϣ
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
	
	//����ͷ��Ϣ
	printf("the width resolution is %d. \n",*(unsigned int *)(buf+0x12));
	printf("the height resolution is %d. \n",*(unsigned int *)(buf+0x16));

	close(fd);
	return 0;
	
}



