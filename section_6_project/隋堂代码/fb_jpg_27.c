/*
 *
 *本文件用来解析jpg图片，并调用fb.c中的显示接口来显示lcd上
 *
 *
 */

#include <stdio.h>
#include <jpeglib.h>
#include <config.h>
#include <jerror.h>



struct my_error_mgr
{  
	struct jpeg_error_mgr pub;	
	//jmp_buf setjmp_buffer;
};
typedef struct my_error_mgr * my_error_ptr;


int is_jpg(const char *path)
{
	return 0;
}

//自己定义的错误处理函数
METHODDEF(void)
my_error_exit (j_common_ptr cinfo)
{  
	//my_error_ptr myerr = (my_error_ptr) cinfo->err;
	//(*cinfo->err->output_message) (cinfo); 
	fprintf(stderr, "my_error_exit\n");
 	//longjmp(myerr->setjmp_buffer, 1);
}


/*
 *函数功能:解码jpg图片，并将解码出来的数据存储
 *函数参数:pPic,记录源jpg图片的信息，解码出来的图片宽高、图片数据缓冲区等信息
 *返回值  :正确返回0，错误返回-1
 */
int jpg_analyze(struct pic_info *pPic)
{
	struct jpeg_decompress_struct cinfo;		//cinfo贯穿整个解码过程的信息记录和传递的数据结构
	struct my_error_mgr jerr;					// 错误处理的
	FILE * infile;								// 指向fopen打开源jpg图片文件的指针
	//JSAMPARRAY buffer;							// 指向解码行数据的指针
	//int row_stride;								// 解码出来的一行图片信息的字节数

	if ((infile = fopen(pPic->pathname, "rb")) == NULL) 
	{   
		fprintf(stderr, "can't open %s\n", pPic->pathname);  
	    return -1;  
	}

	//step1:错误处理函数的绑定，为cinfo分配内存并初始化
	cinfo.err = jpeg_std_error(&jerr.pub); 
	jerr.pub.error_exit = my_error_exit;
	
	// 给解码器做必要的内存分配和数据结构的初始化
	jpeg_create_decompress(&cinfo);

	 //step2:将fopen打开的jpg图片infile和解码器cinfo相关联
	jpeg_stdio_src(&cinfo, infile);

	//step3:读取头信息
	jpeg_read_header(&cinfo, TRUE);

	// 第4步: 启动解码器
	jpeg_start_decompress(&cinfo);

	
	debug("image resolution: %d * %d, bpp/8 = %d.\n ",
	cinfo.output_width, cinfo.output_height, cinfo.output_components); 

	 jpeg_finish_decompress(&cinfo);
	 jpeg_destroy_decompress(&cinfo);
	 fclose(infile);

	return 0;
}







