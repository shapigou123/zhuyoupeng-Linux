#include <linux/module.h>		// module_init  module_exit
#include <linux/init.h>			// __init   __exit
#include <linux/fs.h>
#include <mach/regs-gpio.h>
#include <mach/gpio-bank.h>
#include <linux/ioport.h>
#include <asm/io.h>
#include <linux/leds.h>
#include <mach/gpio.h>
#include <linux/platform_device.h>

#define GPIO_LED1	S5PV210_GPJ0(3)
#define GPIO_LED2	S5PV210_GPJ0(4)
#define GPIO_LED3	S5PV210_GPJ0(5)
#define GPIO_LED4	S5PV210_GPD0(1)
#define X210_LED_ON		0
#define X210_LED_OFF	1

/***************************静态映射*******************************/
#define GPJ0CON		S5PV210_GPJ0CON
#define GPJ0DAT		S5PV210_GPJ0DAT

//#define rGPJ0CON	*((volatile unsigned int *)GPJ0CON)
//#define rGPJ0DAT	*((volatile unsigned int *)GPJ0DAT)
/******************************************************************/

static struct led_classdev mydev1;
static struct led_classdev mydev2;
static struct led_classdev mydev3;
static struct led_classdev mydev4;


static void s5pv210_led1_set(struct led_classdev *led_cdev, enum led_brightness value)
{
	printk(KERN_INFO "s5pv210_led1_set\n");
	
	//writel(0x11111111, GPJ0CON);
	//writel(((1<<3) | (1<<4) | (1<<5)), GPJ0DAT);

	
	if(value == LED_OFF)
		// 用户给了个0，希望LED灭
	{
		//writel((readl(GPJ0DAT) | (1<<3)), GPJ0DAT);
		gpio_set_value(GPIO_LED1, X210_LED_OFF);
	}

	else
	{
		// 用户给的是非0，希望LED亮
		//writel((readl(GPJ0DAT) & ~(1<<3)), GPJ0DAT);
		gpio_set_value(GPIO_LED1, X210_LED_ON);
	}
}



static int s5pv210_led_probe(struct platform_device *dev)
{
	int ret = -1;
/*************************************gpiolib的申请*************************************/	
		// 在这里去申请驱动用到的各种资源，当前驱动中就是GPIO资源
	if (gpio_request(GPIO_LED1, "led1_gpj0.3")) 
	{
		printk(KERN_ERR "gpio_request failed\n");
	} 
	else 
	{
		// 设置为输出模式，并且默认输出1让LED灯灭
		gpio_direction_output(GPIO_LED1, 1);
	}
	
	
/***************************************************************************/
	//LED1
	mydev1.brightness_set = s5pv210_led1_set;
	mydev1.brightness 	 = 0;
	mydev1.name			 = "yyled1";
	ret = led_classdev_register(NULL, &mydev1);
	if (ret < 0) {
		printk(KERN_ERR "led1_classdev_register failed...\n");
		return ret;
	}
	
	return 0;
	
}

static int s5pv210_led_remove(struct platform_device *dev)
{
	led_classdev_unregister(&mydev1);
	printk(KERN_INFO "led1_classdev_unregister\n");

	gpio_free(GPIO_LED1);


	return 0;
}


static struct platform_driver s5pv210_led_driver = {
	.probe		= s5pv210_led_probe,
	.remove		= s5pv210_led_remove,
	.driver		= {
		.name		= "s5pv210-led",
		.owner		= THIS_MODULE,
	},
};

static int __init s5pv210_led_init(void)
{
	
	return platform_driver_register(&s5pv210_led_driver);
	
}

static void __exit s5pv210_led_exit(void)
{
	platform_driver_unregister(&s5pv210_led_driver);
	
}

module_init(s5pv210_led_init);
module_exit(s5pv210_led_exit);

// MODULE_xxx这种宏作用是用来添加模块描述信息
MODULE_LICENSE("GPL");				// 描述模块的许可证
MODULE_AUTHOR("aston");				// 描述模块的作者
MODULE_DESCRIPTION("s5pv210 led driver");	// 描述模块的介绍信息
MODULE_ALIAS("s5pv210_led");			// 描述模块的别名信息








