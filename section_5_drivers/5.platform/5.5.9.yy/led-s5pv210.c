#include <linux/module.h>		// module_init  module_exit
#include <linux/init.h>			// __init   __exit
#include <linux/fs.h>
#include <linux/leds.h>
#include <mach/regs-gpio.h>
#include <mach/gpio-bank.h>
#include <linux/ioport.h>
#include <asm/io.h>

#include <mach/gpio.h>
#include <linux/platform_device.h>
#include <mach/leds-gpio.h>
#include <linux/slab.h>

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

//static struct led_classdev mydev1;
//static struct led_classdev mydev2;
//static struct led_classdev mydev3;
//static struct led_classdev mydev4;


struct s5pv210_gpio_led {
	struct led_classdev		 cdev;
	struct s5pv210_led_platdata	*pdata;
};

//由platform_device类型的指针得到 s5pv210_gpio_led类型的指针
static inline struct s5pv210_gpio_led *pdev_to_gpio(struct platform_device *dev)
{
	return platform_get_drvdata(dev);
}

static inline struct s5pv210_gpio_led *to_gpio(struct led_classdev *led_cdev)
{
	return container_of(led_cdev, struct s5pv210_gpio_led, cdev);
}


static void s5pv210_led_set(struct led_classdev *led_cdev, enum led_brightness value)
{
	
	//writel(0x11111111, GPJ0CON);
	//writel(((1<<3) | (1<<4) | (1<<5)), GPJ0DAT);

	struct s5pv210_gpio_led *led = to_gpio(led_cdev);
	struct s5pv210_led_platdata *pd = led->pdata;
	printk(KERN_INFO "s5pv210_led_set\n");	
	if(value == LED_OFF)
		// 用户给了个0，希望LED灭
	{
		//writel((readl(GPJ0DAT) | (1<<3)), GPJ0DAT);
		gpio_set_value(pd->gpio, X210_LED_OFF);
	}

	else
	{
		// 用户给的是非0，希望LED亮
		//writel((readl(GPJ0DAT) & ~(1<<3)), GPJ0DAT);
		gpio_set_value(pd->gpio, X210_LED_ON);
	}
}



static int s5pv210_led_probe(struct platform_device *dev)
{
	int ret = -1;
	
	struct s5pv210_led_platdata *pdata = dev->dev.platform_data;
	struct s5pv210_gpio_led *led;
	
	printk(KERN_INFO "---------------s5pv210_led_probe---------------\n");
	
	led = kzalloc(sizeof(struct s5pv210_gpio_led), GFP_KERNEL);
	if (led == NULL) {
		dev_err(&dev->dev, "No memory for device\n");
		return -ENOMEM;
	}

	platform_set_drvdata(dev, led);
/*************************************gpiolib的申请*************************************/	
		// 在这里去申请驱动用到的各种资源，当前驱动中就是GPIO资源
	if (gpio_request(pdata->gpio, pdata->name)) 
	{
		printk(KERN_ERR "gpio_request failed\n");
	} 
	else 
	{
		// 设置为输出模式，并且默认输出1让LED灯灭
		gpio_direction_output(pdata->gpio, 1);
	}
	
	
/***************************************************************************/
	//LED1
	led->cdev.brightness_set = s5pv210_led_set;
	led->cdev.brightness 	 = 0;
	led->cdev.name			 = pdata->name;  //led1,led2,led3,led4
	led->pdata = pdata;
	
	ret = led_classdev_register(&dev->dev, &led->cdev); //->优先级较高
	if (ret < 0) {
		printk(KERN_ERR "led_classdev_register failed...\n");
		return ret;
	}
	
	return 0;
	
}

static int s5pv210_led_remove(struct platform_device *dev)
{
	struct s5pv210_gpio_led *led = pdev_to_gpio(dev);
	led_classdev_unregister(&led->cdev);
	printk(KERN_INFO "led_classdev_unregister\n");

	gpio_free(led->pdata->gpio);
	kfree(led);

	return 0;
}


static struct platform_driver s5pv210_led_driver = {
	.probe		= s5pv210_led_probe,
	.remove		= s5pv210_led_remove,
	.driver		= {
		.name		= "s5pv210_led",      //与内核中的platform_device （mach-x210.c中）的名字要一样
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








