#include <linux/module.h>		// module_init  module_exit
#include <linux/init.h>			// __init   __exit
#include <linux/fs.h>
#include <mach/regs-gpio.h>
#include <mach/gpio-bank.h>
#include <linux/ioport.h>
#include <asm/io.h>
#include <linux/leds.h>



/***************************静态映射*******************************/
#define GPJ0CON		S5PV210_GPJ0CON
#define GPJ0DAT		S5PV210_GPJ0DAT

//#define rGPJ0CON	*((volatile unsigned int *)GPJ0CON)
//#define rGPJ0DAT	*((volatile unsigned int *)GPJ0DAT)
/******************************************************************/

static struct led_classdev mydev1;
static struct led_classdev mydev2;
static struct led_classdev mydev3;


static void s5pv210_led1_set(struct led_classdev *led_cdev, enum led_brightness value)
{
	printk(KERN_INFO "s5pv210_led1_set\n");
	
	writel(0x11111111, GPJ0CON);
	//writel(((1<<3) | (1<<4) | (1<<5)), GPJ0DAT);
	
	if(value == LED_OFF)
		// 用户给了个0，希望LED灭
	{
		writel((readl(GPJ0DAT) | (1<<3)), GPJ0DAT);
	}

	else
	{
		// 用户给的是非0，希望LED亮
		writel((readl(GPJ0DAT) & ~(1<<3)), GPJ0DAT);
	}
}

static void s5pv210_led2_set(struct led_classdev *led_cdev, enum led_brightness value)
{
	printk(KERN_INFO "s5pv210_led2_set\n");
	
	writel(0x11111111, GPJ0CON);
	//writel(((1<<3) | (1<<4) | (1<<5)), GPJ0DAT);
	
	if(value == LED_OFF)
		// 用户给了个0，希望LED灭
	{
		writel((readl(GPJ0DAT) | (1<<4)), GPJ0DAT);
	}

	else
	{
		// 用户给的是非0，希望LED亮
		writel((readl(GPJ0DAT) & ~(1<<4)), GPJ0DAT);
	}
}

static void s5pv210_led3_set(struct led_classdev *led_cdev, enum led_brightness value)
{
	printk(KERN_INFO "s5pv210_led3_set\n");
	
	writel(0x11111111, GPJ0CON);
	//writel(((1<<3) | (1<<4) | (1<<5)), GPJ0DAT);
	
	if(value == LED_OFF)
		// 用户给了个0，希望LED灭
	{
		writel((readl(GPJ0DAT) | (1<<5)), GPJ0DAT);
	}

	else
	{
		// 用户给的是非0，希望LED亮
		writel((readl(GPJ0DAT) & ~(1<<5)), GPJ0DAT);
	}
}



static int __init s5pv210_led_init(void)
{
	int ret = -1;
	
	//LED1
	mydev1.brightness_set = s5pv210_led1_set;
	mydev1.brightness 	 = 0;
	mydev1.name			 = "myled1";
	ret = led_classdev_register(NULL, &mydev1);
	if (ret < 0) {
		printk(KERN_ERR "led1_classdev_register failed...\n");
		return ret;
	}
	
		//LED1
	mydev2.brightness_set = s5pv210_led2_set;
	mydev2.brightness 	 = 0;
	mydev2.name			 = "myled2";
	ret = led_classdev_register(NULL, &mydev2);
	if (ret < 0) {
		printk(KERN_ERR "led2_classdev_register failed...\n");
		return ret;
	}
	
		//LED1
	mydev3.brightness_set = s5pv210_led3_set;
	mydev3.brightness 	 = 0;
	mydev3.name			 = "myled3";
	ret = led_classdev_register(NULL, &mydev3);
	if (ret < 0) {
		printk(KERN_ERR "led3_classdev_register failed...\n");
		return ret;
	}
	
	
	return 0;
}

static void __exit s5pv210_led_exit(void)
{
	led_classdev_unregister(&mydev1);
	printk(KERN_INFO "led1_classdev_unregister\n");
	led_classdev_unregister(&mydev2);
	printk(KERN_INFO "led2_classdev_unregister\n");
	led_classdev_unregister(&mydev3);
	printk(KERN_INFO "led3_classdev_unregister\n");
}

module_init(s5pv210_led_init);
module_exit(s5pv210_led_exit);

// MODULE_xxx这种宏作用是用来添加模块描述信息
MODULE_LICENSE("GPL");				// 描述模块的许可证
MODULE_AUTHOR("aston");				// 描述模块的作者
MODULE_DESCRIPTION("s5pv210 led driver");	// 描述模块的介绍信息
MODULE_ALIAS("s5pv210_led");			// 描述模块的别名信息








