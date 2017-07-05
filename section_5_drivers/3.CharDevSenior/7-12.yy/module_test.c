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
#include <linux/device.h>
#include <linux/ioport.h>
//#include <asm-generic/iomap.h>


typedef struct GPJ0REG
{
	volatile unsigned int gpj0con;
	volatile unsigned int gpj0dat;
}gpj0_reg_t;

gpj0_reg_t *pGPJ0REG;

#define MYMAJOR     200
#define MYCNT		1
#define MYNAME      "test_char_device"

//静态映射
#define GPJ0CON S5PV210_GPJ0CON
#define GPJ0DAT S5PV210_GPJ0DAT


#define rGPJ0CON	*((volatile unsigned int *)GPJ0CON)
#define rGPJ0DAT	*((volatile unsigned int *)GPJ0DAT)

#define GPJ0_REGBASE	0xe0200240

//动态映射
#define GPJ0CON_PA	0xe0200240
#define GPJ0DAT_PA 	0xe0200244

#define S5P_GPJ0REG(x)		(x)
#define S5P_GPJ0CON			S5P_GPJ0REG(0)
#define S5P_GPJ0DAT			S5P_GPJ0REG(4)

static void __iomem *baseaddr;

unsigned int *pGPJ0CON;
unsigned int *pGPJ0DAT;



// gpio-bank.h中 宏定义了  #define S5PV210_GPJ0CON	(S5PV210_GPJ0_BASE + 0x00)         
//  S5PV210_GPJ0_BASE在 regs-gpio.h定义的 所以宏展开时要先包含regs-gpio.h，再包含gpio-bank.h。相当于是由内向外



int mymajor;
char kbuf[100];

static dev_t mydev;
//static struct cdev test_cdev;
static struct cdev *pcdev;

static struct class *ptest_class;


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
		//*pGPJ0DAT = ((1<<3)|(1<<4)|(1<<5));
		pGPJ0REG->gpj0dat = ((1<<3) | (1<<4) | (1<<5));
	}
	else if(kbuf[0] == '1')
	{
		//*pGPJ0DAT = ((0<<3)|(0<<4)|(0<<5));
		pGPJ0REG->gpj0dat = ((0<<3) | (0<<4) | (0<<5));
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
	printk(KERN_INFO "chrdev_init\n");
	
//*************************老接口register_chrdev注册字符设备驱动(file_operations)**********************//

//*******使用新的register_chrdev_region/alloc_chrdev_region、cdev_init/cdev_alloc接口来注册***********//
	// 新的接口注册字符设备驱动需要2步
	
	// 第1步：注册/分配主次设备号
	
	
/*	mymajor = register_chrdev(0, MYNAME, &test_fops);
	if (mymajor < 0)
	{
		printk(KERN_ERR "register_chrdev fail\n");
		return -EINVAL;
	}
	printk(KERN_INFO "register_chrdev success... mymajor = %d.\n", mymajor);
*/
	mydev = MKDEV(mymajor, 0);
   // retval = register_chrdev_region(mydev, MYCNT, MYNAME);    
	retval = alloc_chrdev_region(&mydev, 0, MYCNT, MYNAME);	   
	if (retval < 0)
	{
		printk(KERN_ERR "Unable to register minors for %s\n", MYNAME);
		//return -EINVAL;
		goto flag1;
	}
	printk(KERN_INFO "alloc_chrdev_region success");
	printk(KERN_INFO "major = %d, minor = %d.\n", MAJOR(mydev), MINOR(mydev));
	
	
	
	// 第2步：注册字符设备驱动
	//cdev_init(&test_cdev, &test_fops);              //使用cdev_init静态分配，class创建成功MAJOR=250,MINOR=0,DEVNAME=test
	                                                //使用cdev_alloc动态分配时，class创建成功。
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
//	printk(KERN_INFO "cdev_init success\n");
	
	// 注册字符设备驱动完成后，添加设备类的操作，以让内核帮我们发信息
	// 给udev，让udev自动创建和删除设备文件
	ptest_class = class_create(THIS_MODULE, "aston_class");
	
	printk(KERN_INFO "hello world\n");
	
	if (IS_ERR(ptest_class)) 
	{
		return -EINVAL;
	}
	device_create(ptest_class, NULL, mydev, NULL, "test");
	

#if 0
	// 2步完成了映射
	if (!request_mem_region(GPJ0_REGBASE, sizeof(gpj0_reg_t), "GPJ0REG"))
		goto flag3;
	pGPJ0REG = ioremap(GPJ0_REGBASE, sizeof(gpj0_reg_t));
	// 映射之后用指向结构体的指针来进行操作
	// 指针使用->结构体内元素的方式来操作各个寄存器
	pGPJ0REG->gpj0con = 0x11111111;
	pGPJ0REG->gpj0dat = ((0<<3) | (1<<4) | (0<<5));		// 亮
	
#endif	
	
	
#if 1	
// 测试1：用2次ioremap得到的动态映射虚拟地址来操作，测试成功

	if (!request_mem_region(GPJ0CON_PA, 4, "GPJ0CON"))
		return -EINVAL;
	if (!request_mem_region(GPJ0DAT_PA, 4, "GPJ0CON"))
		return -EINVAL;
	
	pGPJ0CON = ioremap(GPJ0CON_PA, 4);
	pGPJ0DAT = ioremap(GPJ0DAT_PA, 4);
	writel(0x11111111, pGPJ0CON);
	writel(((0<<3) | (0<<4) | (0<<5)), pGPJ0DAT);
#endif

#if 0	
	// 测试2：用静态映射的虚拟地址来操作，测试成功
	writel(0x11111111, GPJ0CON);
	writel(((0<<3) | (0<<4) | (0<<5)), GPJ0DAT);
#endif

#if 0	
	// 测试3：用1次ioremap映射多个寄存器得到虚拟地址，测试成功
	if (!request_mem_region(GPJ0CON_PA, 8, "GPJ0BASE"))
		goto flag3;
	baseaddr = ioremap(GPJ0CON_PA, 8);
	
	writel(0x11111111, baseaddr + S5P_GPJ0CON);
	writel(((0<<3) | (0<<4) | (0<<5)), baseaddr + S5P_GPJ0DAT);
#endif
	
return 0;	


	//release_mem_region(GPJ0_REGBASE, sizeof(gpj0_reg_t));
	release_mem_region(GPJ0CON_PA, 4);
	release_mem_region(GPJ0DAT_PA, 4);
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
	printk(KERN_INFO "chrdev_exit: rmmod sucess\n");
	
  // 	pGPJ0REG->gpj0dat = ((1<<3) | (0<<4) | (1<<5));
	writel(((1<<3) | (1<<4) | (1<<5)), pGPJ0DAT);	
	writel(((1<<3) | (1<<4) | (1<<5)), GPJ0DAT);
	iounmap(pGPJ0CON);
	iounmap(pGPJ0DAT);
	release_mem_region(GPJ0CON_PA, 4);
	release_mem_region(GPJ0DAT_PA, 4);
	//iounmap(pGPJ0REG);
	//release_mem_region(GPJ0_REGBASE, sizeof(gpj0_reg_t));

	device_destroy(ptest_class, mydev);
	class_destroy(ptest_class);

	//unregister_chrdev(mymajor, MYNAME);


	// 使用新的接口来注销字符设备驱动
	// 注销分2步：
	// 第一步真正注销字符设备驱动用cdev_del
	cdev_del(pcdev);
	//cdev_del(&test_cdev);
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








