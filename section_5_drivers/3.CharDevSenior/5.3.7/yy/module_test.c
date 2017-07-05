#include <linux/module.h>		// module_init  module_exit
#include <linux/init.h>			// __init   __exit
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <mach/regs-gpio.h>
#include <mach/gpio-bank.h>
#include <linux/string.h>
#include <linux/ioport.h>
#include <asm/io.h>
#include <linux/cdev.h>
#include <linux/device.h>

#define MYMAJOR		200
#define MYNAME		"test_chrdev"
#define MYCNT		1

/***************************静态映射*******************************/
#define GPJ0CON		S5PV210_GPJ0CON
#define GPJ0DAT		S5PV210_GPJ0DAT

#define rGPJ0CON	*((volatile unsigned int *)GPJ0CON)
#define rGPJ0DAT	*((volatile unsigned int *)GPJ0DAT)
/***************************静态映射*******************************/


#define GPJ0BASE_PA	0xE0200240

static unsigned int *pGPJ0CON;
static unsigned int *pGPJ0DAT;

static dev_t mydev;
//static struct cdev test_cdev;
//static int mymajor;
static struct cdev *pcdev;
static struct class *test_class;
static char kbuf[100];

static int test_chrdev_open(struct inode *inode, struct file *file)
{
	printk(KERN_INFO "test_chrdev_open...\n");
	//printk(KERN_INFO "rGPJ0CON = %p, rGPJ0DAT = %p\n", GPJ0CON, GPJ0DAT);
	//rGPJ0CON = 0x11111111;
	return 0;
}

static int test_chrdev_release(struct inode *inode, struct file *file)
{
	printk(KERN_INFO "test_chrdev_release...\n");
	return 0;
}

ssize_t test_chrdev_read(struct file *file, char __user *ubuf, size_t size, loff_t *ppos)
{
	printk(KERN_INFO "test_chrdev_read...\n");
	
	if(copy_to_user(ubuf, kbuf, size))
		return -EINVAL;
	printk(KERN_INFO "copy_to_user success\n");
	
	return 0;
}

// 写函数的本质就是将应用层传递过来的数据先复制到内核中，然后将之以正确的方式写入硬件完成操作。
static ssize_t test_chrdev_write(struct file *file, const char __user *ubuf, size_t count, loff_t *ppos)
{
	printk(KERN_INFO "test_chrdev_write...\n");
	
	memset(kbuf, 0, sizeof(kbuf));
	// 使用该函数将应用层传过来的ubuf中的内容拷贝到驱动空间中的一个buf中
	if(copy_from_user(kbuf, ubuf, count))
		return -EINVAL;
	printk(KERN_INFO "copy_from_user success\n");	
	
	// 真正的驱动中，数据从应用层复制到驱动中后，我们就要根据这个数据
	// 去写硬件完成硬件的操作。所以这下面就应该是操作硬件的代码
#if 0	
	if(!strcmp(kbuf, "on"))
		rGPJ0DAT = ((0<<3) | (0<<4) | (0<<5));
	else if(!strcmp(kbuf, "off"))
		rGPJ0DAT = ((1<<3) | (1<<4) | (1<<5));
#endif

#if 1
	if(kbuf[0] == '1')
		rGPJ0DAT = ((0<<3) | (0<<4) | (0<<5));
	else if(kbuf[0] == '0')
		rGPJ0DAT = ((1<<3) | (1<<4) | (1<<5));
#endif
	return 0;
}

static const struct file_operations test_fops = {
	.owner		= THIS_MODULE,
	.open		= test_chrdev_open,
	.release	= test_chrdev_release,
	.read		= test_chrdev_read,
	.write		= test_chrdev_write,
};

// 模块安装函数
static int __init chrdev_init(void)
{	
	printk(KERN_INFO "chrdev_init init\n");
	//printk("<7>" "chrdev_init init\n");
	//printk("<7> chrdev_init init\n");
	

/**********************老接口注册驱动**********************************/
#if 0
	mymajor = register_chrdev(0, MYNAME, &test_fops);
	if (mymajor < 0)
	{
		printk(KERN_ERR "register_chrdev failed...\n");
		return -EINVAL;
	}
	printk(KERN_INFO "register_chrdev success...mymajor is %d\n", mymajor);
#endif	
/**********************************************************************/



/**********************新接口注册驱动之register_chrdev_region**********************************/
#if 0
//第一步注册设备号	
	mydev = MKDEV(MYMAJOR, 0);
	if(register_chrdev_region(mydev, MYCNT, MYNAME))
	{
		printk(KERN_ERR "Unable to register minors for %s\n", MYNAME);
		return -EINVAL;
	}	
	printk(KERN_INFO "register_chrdev_region success...\n");
#endif


/**********************新接口注册驱动之alloc_chrdev_region***********/
	if(alloc_chrdev_region(&mydev, 12, MYCNT, MYNAME))
	{
		printk(KERN_ERR "alloc_chrdev_region failed\n");
		//return -EINVAL;
		goto flag1;
	}	
	printk(KERN_INFO "alloc_chrdev_region success...\n");
	printk(KERN_INFO "major = %d, minor = %d \n", MAJOR(mydev), MINOR(mydev));
	
//第二步注册字符设备驱动	
	pcdev = cdev_alloc();
	//cdev_init(&test_cdev, &test_fops);
	cdev_init(pcdev, &test_fops);
	//if(cdev_add(&test_cdev, mydev, MYCNT))
	if(cdev_add(pcdev, mydev, MYCNT))
	{
		printk(KERN_ERR "Unable to cdev_add\n");
		//return -EINVAL;
		goto flag2;
	}	
	printk(KERN_INFO "cdev_add success...\n");

/**********************************************************************/



/********************************动态映射******************************/

	if(!request_mem_region(GPJ0BASE_PA, 8, "GPJ0BASE"))
		//return -EINVAL;	
	goto flag3;
	
	
	pGPJ0CON = ioremap(GPJ0BASE_PA, 8);
	pGPJ0DAT = pGPJ0CON + 1;
	
	*pGPJ0CON =	 0x11111111;
	*pGPJ0DAT = ((0<<3)|(1<<4)|(0<<5));
	
/********************************动态映射******************************/


/********************************udev自动创建设备文件*****************/

    test_class = class_create(THIS_MODULE, "yy_class");
	if (IS_ERR(test_class))
		return -EINVAL;
	device_create(test_class, NULL, mydev, NULL, "test");


/******************************************************************/
	return 0;
	
flag3:
	cdev_del(pcdev);
	//cdev_del(&test_cdev);
flag2:
	unregister_chrdev_region(mydev, MYCNT);
flag1:
	return -EINVAL;
}



// 模块卸载函数
static void __exit chrdev_exit(void)
{
	printk(KERN_INFO "chrdev_exit exit\n");
	
	
	device_destroy(test_class, mydev);
	class_destroy(test_class);
	
/************************老接口卸载驱动********************************/
#if 0
	//在这里卸载驱动
	unregister_chrdev(mymajor, MYNAME);
	printk(KERN_INFO "unregister_chrdev success...\n");
#endif	
/**********************************************************************/

	
/************************新接口卸载驱动********************************/	

	//cdev_del(&test_cdev);
	cdev_del(pcdev);
	unregister_chrdev_region(mydev, MYCNT);

/**********************************************************************/


/*************************动态映射解除*********************************/

	*pGPJ0DAT = ((1<<3) | (0<<4) | (1<<5));	
	iounmap(pGPJ0CON);
	release_mem_region(GPJ0BASE_PA, 8);
	
/**********************************************************************/
	
}


module_init(chrdev_init);
module_exit(chrdev_exit);

// MODULE_xxx这种宏作用是用来添加模块描述信息
MODULE_LICENSE("GPL");				// 描述模块的许可证
MODULE_AUTHOR("aston");				// 描述模块的作者
MODULE_DESCRIPTION("module test");	// 描述模块的介绍信息
MODULE_ALIAS("alias xxx");			// 描述模块的别名信息








