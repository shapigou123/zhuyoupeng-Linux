#include <linux/module.h>		// module_init  module_exit
#include <linux/init.h>			// __init   __exit
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <mach/regs-gpio.h>
#include <mach/gpio-bank.h>
#include <linux/ioport.h>
#include <linux/string.h>
#include <linux/io.h>
#include <linux/cdev.h>
//#include <asm-generic/iomap.h>


#define MYMAJOR     200
#define MYCNT		1
#define MYNAME      "test_char_device"

//静态映射
#define GPJ0CON S5PV210_GPJ0CON
#define GPJ0DAT S5PV210_GPJ0DAT


#define rGPJ0CON	*((volatile unsigned int *)GPJ0CON)
#define rGPJ0DAT	*((volatile unsigned int *)GPJ0DAT)
//动态映射
#define GPJ0CON_PA	0xe0200240
#define GPJ0DAT_PA 	0xe0200244

unsigned int *pGPJ0CON;
unsigned int *pGPJ0DAT;

// gpio-bank.h中 宏定义了  #define S5PV210_GPJ0CON	(S5PV210_GPJ0_BASE + 0x00)         
//  S5PV210_GPJ0_BASE在 regs-gpio.h定义的 所以宏展开时要先包含regs-gpio.h，再包含gpio-bank.h。相当于是由内向外

//int mymajor;
char kbuf[100];

static dev_t mydev;
static struct cdev test_cdev;
static struct cdev *pcdev;


/*****************************打开文件******************************/
static int test_chrdev_open(struct inode *inode, struct file *file)
{
	// 这个函数中真正应该放置的是打开这个设备的硬件操作代码部分
	printk(KERN_INFO "test_chrdev_open\n");
	//rGPJ0CON = 0x11111111;
	//rGPJ0DAT = ((0<<3)|(0<<4)|(0<<5));
	
	return 0;
	
}

/*****************************关闭文件******************************/
static int test_chrdev_release(struct inode *inode, struct file *file)
{
	printk(KERN_INFO "test_chrdev_release\n");
	//rGPJ0DAT = ((1<<3)|(1<<4)|(1<<5));
	return 0;
}

/*****************************读函数实体（驱动——>应用）******************************/
ssize_t test_chrdev_read(struct file *file, char __user *ubuf,size_t count, loff_t *ppos)
{
	int ret = -1;
	printk(KERN_INFO "test_chrdev_read\n");
		
	ret = copy_to_user(ubuf, kbuf, count);
	
	if(ret)
	{
		printk(KERN_ERR "copy_to_user\n");
		return (-EINVAL);
	}
	
	printk(KERN_INFO "copy_to_user succsee...\n");
	
	return 0;
}

/***************************** 写函数实体（应用——>驱动）******************************/
static ssize_t test_chrdev_write(struct file *file,const char __user *ubuf,size_t count, loff_t *ppos)
{
	int ret = -1;
	
	printk(KERN_INFO "test_chrdev_write\n");
	
	ret = copy_from_user(kbuf, ubuf, count);
	
	if(ret)
	{
		printk(KERN_ERR "copy_from_user\n");
		return (-EINVAL);
	}
	
	printk(KERN_INFO "copy_from_user succsee...\n");
	
#if 0	
	if(kbuf[0] == '0')
	{
		rGPJ0DAT = ((1<<3)|(1<<4)|(1<<5));
	}
	else if(kbuf[0] == '1')
	{
		rGPJ0DAT = ((0<<3)|(0<<4)|(0<<5));
	}
#endif	


	if(kbuf[0] == '0')
	{
		*pGPJ0DAT = ((1<<3)|(1<<4)|(1<<5));
	}
	else if(kbuf[0] == '1')
	{
		*pGPJ0DAT = ((0<<3)|(0<<4)|(0<<5));
	}
		
	
	return 0;
	
}


/***************************** file_operations******************************/
static const struct file_operations test_fops = {
	.owner		= THIS_MODULE,
	//.unlocked_ioctl	= tw_chrdev_ioctl,
	.open		= test_chrdev_open,
	.release	= test_chrdev_release,
	.write      = test_chrdev_write,
	.read       = test_chrdev_read,
};

/***************************** 模块安装函数******************************/
static int __init chrdev_init(void)
{	
	int retval;
	printk(KERN_INFO "chrdev_init: insmod sucess\n");
	//printk("<7>" "chrdev_init helloworld init\n");
	//printk("<7> chrdev_init helloworld init\n");
	
/****************************老接口register_chrdev注册字符设备驱动(file_operations)************************/
#if 0   
	mymajor = register_chrdev(0, MYNAME, &test_fops);
	
	if(mymajor < 0)
	{
		printk(KERN_ERR "register_ chrdev fail\n");
        return(-EINVAL);
	}
	printk(KERN_INFO "register_chrdev sueccess... MYmajor: %d, devices name is: %s \n",mymajor,MYNAME);
	
#endif

/*******使用新的register_chrdev_region/alloc_chrdev_region、cdev_init/cdev_alloc接口来注册***********/
	// 新的接口注册字符设备驱动需要2步
	
	// 第1步：注册/分配主次设备号
	//mydev = MKDEV(MYMAJOR, 0);
   // retval = register_chrdev_region(mydev, MYCNT, MYNAME);    
	retval = alloc_chrdev_region(&mydev, 0, MYCNT, MYNAME);	
	if (retval < 0)
	{
		printk(KERN_ERR "Unable to register minors for %s\n", MYNAME);
		//return -EINVAL;
		goto flag1;
	}
	printk(KERN_INFO "register_chrdev_region success");
	printk(KERN_INFO "major = %d, minor = %d.\n", MAJOR(mydev), MINOR(mydev));
	
	
	
	// 第2步：注册字符设备驱动
	//cdev_init(&test_cdev, &test_fops);
	//retval = cdev_add(&test_cdev, mydev, MYCNT);
	pcdev = cdev_alloc();
	pcdev->owner = THIS_MODULE;
	pcdev->ops = &test_fops;
	
	retval = cdev_add(pcdev, mydev, MYCNT);
		
	if (retval) 
	{
		printk(KERN_ERR "Unable to get cdev_add \n");
		goto flag2;
	}
	printk(KERN_INFO "cdev_add success\n");
#if 1	
	if(!request_mem_region(GPJ0CON_PA, 8, "GPJ0CON"))
		//return -EINVAL;	
    goto flag3;
	pGPJ0CON = ioremap(GPJ0CON_PA, 8);
	pGPJ0DAT = pGPJ0CON + 1;

	*pGPJ0CON = 0x11111111;
	*pGPJ0DAT = ((0<<3) | (1<<4) | (0<<5));	
	
	return 0;
#endif	

//flag4:
	release_mem_region(GPJ0CON_PA, 8);
flag3:
	cdev_del(&test_cdev);
flag2:
	unregister_chrdev_region(mydev, MYCNT);
flag1:
	return -EINVAL;
	

	
}


// 模块卸载函数
static void __exit chrdev_exit(void)
{
	printk(KERN_INFO "chrdev_exit: rmmod sucess\n");
	
    *pGPJ0DAT = ((1<<3) | (0<<4) | (1<<5));	
	
#if 1

	iounmap(pGPJ0CON);
	release_mem_region(GPJ0CON_PA, 8);

#endif	
/***************************注册file_operations************************/

#if 0
// 在module_exit宏调用的函数中去注销字符设备驱动
	unregister_chrdev(Mymajor, MYNAME);
#endif

	// 使用新的接口来注销字符设备驱动
	// 注销分2步：
	// 第一步真正注销字符设备驱动用cdev_del
	cdev_del(&test_cdev);
	// 第二步去注销申请的主次设备号
	unregister_chrdev_region(mydev, MYCNT);

	printk(KERN_INFO "unregister_chrdev\n");
	

	
}


module_init(chrdev_init);
module_exit(chrdev_exit);

// MODULE_xxx这种宏作用是用来添加模块描述信息
MODULE_LICENSE("GPL");				// 描述模块的许可证
MODULE_AUTHOR("aston");				// 描述模块的作者
MODULE_DESCRIPTION("module test");	// 描述模块的介绍信息
MODULE_ALIAS("alias xxx");			// 描述模块的别名信息








