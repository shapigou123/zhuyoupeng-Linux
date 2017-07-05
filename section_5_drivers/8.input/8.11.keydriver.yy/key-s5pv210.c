#include <linux/input.h> 
#include <linux/module.h> 
#include <linux/init.h>
#include <asm/irq.h> 
#include <asm/io.h>

#include <mach/irqs.h>		//arch/arm/mach-s5pv210/include/mach
#include <linux/interrupt.h>
#include <linux/gpio.h>

/*
 * X210:
 *
 * POWER  -> EINT1   -> GPH0_1
 * LEFT   -> EINT2   -> GPH0_2
 * DOWN   -> EINT3   -> GPH0_3
 * UP     -> KP_COL0 -> GPH2_0
 * RIGHT  -> KP_COL1 -> GPH2_1
 * MENU   -> KP_COL3 -> GPH2_3 (KEY_A)
 * BACK   -> KP_COL2 -> GPH2_2 (KEY_B)
 */
 
#define		BUTTON_LEFT_IRQ		IRQ_EINT2
#define		BUTTON_DOWN_IRQ		IRQ_EINT3

#define IRQF_TRIGGER_RISING	    0x00000001
#define IRQF_TRIGGER_FALLING	0x00000002
 
static struct input_dev *button_dev;

static irqreturn_t button_left_interrupt(int irq, void *dummy)  
//irq 是中断号，与request_irq里的中断号相互确认。dummy用于共享中断，是发生中断时驱动对应的数据，用它来区分中断。
{
	int flag;

	s3c_gpio_cfgpin(S5PV210_GPH0(2), S3C_GPIO_SFN(0x0));		// input模式
	flag = gpio_get_value(S5PV210_GPH0(2));
	s3c_gpio_cfgpin(S5PV210_GPH0(2), S3C_GPIO_SFN(0x0f));		// eint2模式
	
	input_report_key(button_dev, KEY_LEFT, !flag); //向上层汇报按键事件。
	//inb(BUTTON_PORT) & 1， 是键值。若按下按键，GPIO的值是0，代表有按键，则要返回1.
	
	input_sync(button_dev);									   //加一个同步包。
	return IRQ_HANDLED; 									  //中断处理程序正确执行。在操作系统中，中断处理程序中有返回值，操作系统要对它进行监管。
}

static irqreturn_t button_down_interrupt(int irq, void *dummy)  
{
	int flag;

	s3c_gpio_cfgpin(S5PV210_GPH0(3), S3C_GPIO_SFN(0x0));		// input模式
	flag = gpio_get_value(S5PV210_GPH0(3));
	s3c_gpio_cfgpin(S5PV210_GPH0(3), S3C_GPIO_SFN(0x0f));		// eint2模式	
	input_report_key(button_dev, KEY_DOWN, !flag); 
	input_sync(button_dev);									  
	return IRQ_HANDLED; 									  
}

static int __init button_init(void) 
{
	int error;
	
	error = gpio_request(S5PV210_GPH0(2), "GPH0_2");
	if(error)
		printk("key-s5pv210: request gpio GPH0(2) fail");
	
	s3c_gpio_cfgpin(S5PV210_GPH0(2), S3C_GPIO_SFN(0x0f));		// eint2模式
	
	error = gpio_request(S5PV210_GPH0(3), "GPH0_3");
	if(error)
		printk("key-s5pv210: request gpio GPH0(3) fail");
	
	s3c_gpio_cfgpin(S5PV210_GPH0(3), S3C_GPIO_SFN(0x0f));		// eint2模式
	
	//申请一个中断，与request_gpio类似
	if (request_irq(BUTTON_LEFT_IRQ, button_left_interrupt, IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING, "button-x210", NULL)) 
	{
		printk(KERN_ERR "key-s5pv210.c: Can't allocate irq %d\n", BUTTON_LEFT_IRQ);
        return -EBUSY; 
	}
	if (request_irq(BUTTON_DOWN_IRQ, button_down_interrupt, IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING, "button-x210", NULL)) 
	{
		printk(KERN_ERR "key-s5pv210.c: Can't allocate irq %d\n", BUTTON_DOWN_IRQ);
        return -EBUSY; 
	}
	button_dev = input_allocate_device();
	
	if (!button_dev)
	{ 
		printk(KERN_ERR "key-s5pv210.c: Not enough memory\n");
		error = -ENOMEM;
		goto err_free_irq; 
	}
	//注册KEY事件
	button_dev->evbit[0] = BIT_MASK(EV_KEY);	//这是比较老的方法，没有用set_bit(EV_KEY, button_dev->evbit);
	
	button_dev->keybit[BIT_WORD(KEY_LEFT)] = BIT_MASK(KEY_LEFT);//set_bit(BTN_0, button_dev->keybit);
	//KEY_LEFT 是按键键码,值为105
	
	button_dev->keybit[BIT_WORD(KEY_DOWN)] = BIT_MASK(KEY_DOWN);
	
	error = input_register_device(button_dev);
	if (error) 
	{ 
		printk(KERN_ERR "key-s5pv210.c: Failed to register device\n");
		goto err_free_dev;
	}
	return 0;
	
 err_free_dev:
	input_free_device(button_dev);
	
 err_free_irq:
	free_irq(BUTTON_LEFT_IRQ, button_left_interrupt);
	free_irq(BUTTON_DOWN_IRQ, button_down_interrupt);	
	
	return error; 
}
static void __exit button_exit(void)
{
	 input_unregister_device(button_dev); //前面用了allocate，这里夹杂了free
	 free_irq(BUTTON_LEFT_IRQ, button_left_interrupt);
	 free_irq(BUTTON_DOWN_IRQ, button_down_interrupt);	 
}
module_init(button_init); 
module_exit(button_exit); 

MODULE_LICENSE("GPL");
MODULE_AUTHOR("yuyang 563594467@qq.com>");
MODULE_DESCRIPTION("Keyboard driver for s3c button.");
MODULE_ALIAS("platform:s3c-button");
