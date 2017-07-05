CC		= arm-linux-gcc
LD 		= arm-linux-ld
OBJCOPY	= arm-linux-objcopy
OBJDUMP	= arm-linux-objdump
AR		= arm-linux-ar
 
INCDIR	:= $(shell pwd)                                 //定义一个变量，后面直接引用就可以了
# C预处理器的flag，flag就是编译器可选的选项
CPPFLAGS	:= -nostdlib -nostdinc -I$(INCDIR)/include  //不使用标准库；不使用标准头文件；-I 指定头文件目录 
# C编译器的flag
CFLAGS		:= -Wall -O2 -fno-builtin                   // 警告；优化等级；不使用标准库，也不要使用编译器添加的头文件

#导出这些变量到全局，其实就是给子文件夹下面的Makefile使用
export CC LD OBJCOPY OBJDUMP AR CPPFLAGS CFLAGS


objs := start.o led.o clock.o uart.o main.o 
objs += lib/libc.a

uart.bin: $(objs)
	$(LD) -Tlink.lds -o uart.elf $^
	$(OBJCOPY) -O binary uart.elf uart.bin
	$(OBJDUMP) -D uart.elf > uart_elf.dis
	gcc mkv210_image.c -o mkx210
	./mkx210 uart.bin 210.bin

lib/libc.a:
	cd lib;	make;	cd ..                               //给定lib/libc.a一个规则！！ 进入子目录；然后make;再退出
	
%.o : %.S
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $< -c            //规则，找相关的 .s文件来生成.o

%.o : %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $< -c            //找相关的 .c文件来生成.o文件

clean:
	rm *.o *.elf *.bin *.dis mkx210 -f
	cd lib; make clean; cd ..

	
	