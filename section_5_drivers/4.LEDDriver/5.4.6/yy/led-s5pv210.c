#include <linux/module.h>		// module_init  module_exit
#include <linux/init.h>			// __init   __exit
#include <linux/fs.h>
#include <mach/regs-gpio.h>
#include <mach/gpio-bank.h>
#include <linux/ioport.h>
#include <asm/io.h>
#include <linux/leds.h>

static struct led_classdev mydev;
/***************************静态映射*******************************/
#define GPJ0CON		S5PV210_GPJ0CON
#define GPJ0DAT		S5PV210_GPJ0DAT

#define rGPJ0CON	*((volatile unsigned int *)GPJ0CON)
#define rGPJ0DAT	*((volatile unsigned int *)GPJ0DAT)
/******************************************************************/


static void s5pv210_led_set(struct led_classdev *led_cdev, enum led_brightness value)
{
	printk(KERN_INFO "s5pv210_led_set\n");

	if(value == LED_OFF)
		// 用户给了个0，希望LED灭
	{
		writel(0x11111111, GPJ0CON);
		writel(((1<<3) | (1<<4) | (1<<5)), GPJ0DAT);
	}
	else
	{
		// 用户给的是非0，希望LED亮
		writel(0x11111111, GPJ0CON);
		writel(((0<<3) | (0<<4) | (0<<5)), GPJ0DAT);
	}
}



static int __init s5pv210_led_init(void)
{
	int ret = -1;
	mydev.brightness_set = s5pv210_led_set;
	
	mydev.brightness 	 = 255;
	mydev.name			 = "myled";
	ret = led_classdev_register(NULL, &mydev);
	if (ret < 0) {
		printk(KERN_ERR "led_classdev_register failed...\n");
		return ret;
	}
	return 0;
}

static void __exit s5pv210_led_exit(void)
{
	led_classdev_unregister(&mydev);
}

module_init(s5pv210_led_init);
module_exit(s5pv210_led_exit);

// MODULE_xxx这种宏作用是用来添加模块描述信息
MODULE_LICENSE("GPL");				// 描述模块的许可证
MODULE_AUTHOR("aston");				// 描述模块的作者
MODULE_DESCRIPTION("s5pv210 led driver");	// 描述模块的介绍信息
MODULE_ALIAS("s5pv210_led");			// 描述模块的别名信息








