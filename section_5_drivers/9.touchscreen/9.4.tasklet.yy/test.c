#include <linux/init.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kfifo.h>
#include <linux/time.h>
#include <linux/interrupt.h>

void print_current_time(int);

MODULE_LICENSE("Dual BSD/GPL");

static void my_tasklet_func(unsigned long);

/* mytasklet 必须定义在testtasklet_init函数的外面，否则会出错 */
DECLARE_TASKLET(mytasklet, my_tasklet_func, 1000);

static int testtasklet_init(void)
{
    printk(KERN_ALERT "interrupt's top half!\n");

    // 如果在这里定义的话，那么 mytasklet是函数的局部变量，
    // 后面调度的时候会找不到 mytasklet
    // DECLARE_TASKLET(mytasklet, my_tasklet_func, 1000);

    // 调度tasklet， 处理器会在适当时候执行这个tasklet
    tasklet_schedule(&mytasklet);
    
    return 0;
    
}

static void testtasklet_exit(void)
{
    printk(KERN_ALERT "*************************\n");
    print_current_time(0);
    printk(KERN_ALERT "testtasklet is exited!\n");
    printk(KERN_ALERT "*************************\n");
        
}

static void my_tasklet_func(unsigned long data)
{
    printk(KERN_ALERT "=========================\n");
    print_current_time(0);
    printk(KERN_ALERT "my tasklet function is been called!....\n");
    printk(KERN_ALERT "parameter data is %ld\n", data);
    printk(KERN_ALERT "=========================\n");
}

module_init(testtasklet_init);
module_exit(testtasklet_exit);