#include <linux/module.h>		// module_init  module_exit
#include <linux/init.h>			// __init   __exit
#include <linux/fs.h>
#include <asm/uaccess.h>

#define MYMAJOR		200
#define MYNAME		"test_chrdev"

static int mymajor;
static char kbuf[100];
static int test_chrdev_open(struct inode *inode, struct file *file)
{
	printk(KERN_INFO "test_chrdev_open...\n");
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
	
	// 使用该函数将应用层传过来的ubuf中的内容拷贝到驱动空间中的一个buf中
	if(copy_from_user(kbuf, ubuf, count))
		return -EINVAL;
	printk(KERN_INFO "copy_from_user success\n");	
	
	// 真正的驱动中，数据从应用层复制到驱动中后，我们就要根据这个数据
	// 去写硬件完成硬件的操作。所以这下面就应该是操作硬件的代码
	
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
	//printk("<7>" "chrdev_init helloworld init\n");
	//printk("<7> chrdev_init helloworld init\n");

	//在这里注册驱动
	mymajor = register_chrdev(0, MYNAME, &test_fops);
	if (mymajor < 0)
	{
		printk(KERN_ERR "register_chrdev failed...\n");
		return -EINVAL;
	}
	
	printk(KERN_INFO "register_chrdev success...mymajor is %d\n", mymajor);
	return 0;
}

// 模块卸载函数
static void __exit chrdev_exit(void)
{
	printk(KERN_INFO "chrdev_exit exit\n");
	//在这里卸载驱动
	unregister_chrdev(mymajor, MYNAME);
	printk(KERN_INFO "unregister_chrdev success...\n");
}


module_init(chrdev_init);
module_exit(chrdev_exit);

// MODULE_xxx这种宏作用是用来添加模块描述信息
MODULE_LICENSE("GPL");				// 描述模块的许可证
MODULE_AUTHOR("aston");				// 描述模块的作者
MODULE_DESCRIPTION("module test");	// 描述模块的介绍信息
MODULE_ALIAS("alias xxx");			// 描述模块的别名信息








