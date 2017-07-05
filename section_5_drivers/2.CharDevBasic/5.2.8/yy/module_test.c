#include <linux/module.h>		// module_init  module_exit
#include <linux/init.h>			// __init   __exit
#include <linux/fs.h>

#define MYMAJOR		200
#define MYNAME		"test_chrdev"



static int test_chrdev_open(struct inode *inode, struct file *file)
{
	printk(KERN_INFO "test_chrdev_open success...\n");
	return 0;
}

static int test_chrdev_close(struct inode *inode, struct file *file)
{
	printk(KERN_INFO "test_chrdev_close success...\n");
	return 0;
}

static const struct file_operations test_fops = {
	.owner		= THIS_MODULE,
	.open		= test_chrdev_open,
	.release	= test_chrdev_close,
};

// 模块安装函数
static int __init chrdev_init(void)
{	
	int ret = -1;
	printk(KERN_INFO "chrdev_init init\n");
	//printk("<7>" "chrdev_init helloworld init\n");
	//printk("<7> chrdev_init helloworld init\n");

	//在这里注册驱动
	ret = register_chrdev(MYMAJOR, MYNAME, &test_fops);
	if (ret)
	{
		printk(KERN_ERR "register_chrdev failed...\n");
		return -EINVAL;
	}
	
	printk(KERN_INFO "register_chrdev success...\n");
	return 0;
}

// 模块卸载函数
static void __exit chrdev_exit(void)
{
	printk(KERN_INFO "chrdev_exit exit\n");
	//在这里卸载驱动
	unregister_chrdev(MYMAJOR, MYNAME);
	printk(KERN_INFO "unregister_chrdev success...\n");
}


module_init(chrdev_init);
module_exit(chrdev_exit);

// MODULE_xxx这种宏作用是用来添加模块描述信息
MODULE_LICENSE("GPL");				// 描述模块的许可证
MODULE_AUTHOR("aston");				// 描述模块的作者
MODULE_DESCRIPTION("module test");	// 描述模块的介绍信息
MODULE_ALIAS("alias xxx");			// 描述模块的别名信息








