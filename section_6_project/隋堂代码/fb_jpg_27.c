/*
 *
 *���ļ���������jpgͼƬ��������fb.c�е���ʾ�ӿ�����ʾlcd��
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

//�Լ�����Ĵ�������
METHODDEF(void)
my_error_exit (j_common_ptr cinfo)
{  
	//my_error_ptr myerr = (my_error_ptr) cinfo->err;
	//(*cinfo->err->output_message) (cinfo); 
	fprintf(stderr, "my_error_exit\n");
 	//longjmp(myerr->setjmp_buffer, 1);
}


/*
 *��������:����jpgͼƬ������������������ݴ洢
 *��������:pPic,��¼ԴjpgͼƬ����Ϣ�����������ͼƬ��ߡ�ͼƬ���ݻ���������Ϣ
 *����ֵ  :��ȷ����0�����󷵻�-1
 */
int jpg_analyze(struct pic_info *pPic)
{
	struct jpeg_decompress_struct cinfo;		//cinfo�ᴩ����������̵���Ϣ��¼�ʹ��ݵ����ݽṹ
	struct my_error_mgr jerr;					// �������
	FILE * infile;								// ָ��fopen��ԴjpgͼƬ�ļ���ָ��
	//JSAMPARRAY buffer;							// ָ����������ݵ�ָ��
	//int row_stride;								// ���������һ��ͼƬ��Ϣ���ֽ���

	if ((infile = fopen(pPic->pathname, "rb")) == NULL) 
	{   
		fprintf(stderr, "can't open %s\n", pPic->pathname);  
	    return -1;  
	}

	//step1:���������İ󶨣�Ϊcinfo�����ڴ沢��ʼ��
	cinfo.err = jpeg_std_error(&jerr.pub); 
	jerr.pub.error_exit = my_error_exit;
	
	// ������������Ҫ���ڴ��������ݽṹ�ĳ�ʼ��
	jpeg_create_decompress(&cinfo);

	 //step2:��fopen�򿪵�jpgͼƬinfile�ͽ�����cinfo�����
	jpeg_stdio_src(&cinfo, infile);

	//step3:��ȡͷ��Ϣ
	jpeg_read_header(&cinfo, TRUE);

	// ��4��: ����������
	jpeg_start_decompress(&cinfo);

	
	debug("image resolution: %d * %d, bpp/8 = %d.\n ",
	cinfo.output_width, cinfo.output_height, cinfo.output_components); 

	 jpeg_finish_decompress(&cinfo);
	 jpeg_destroy_decompress(&cinfo);
	 fclose(infile);

	return 0;
}







