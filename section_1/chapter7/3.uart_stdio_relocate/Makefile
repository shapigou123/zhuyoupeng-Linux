CC		= arm-linux-gcc
LD 		= arm-linux-ld
OBJCOPY	= arm-linux-objcopy
OBJDUMP	= arm-linux-objdump
AR		= arm-linux-ar


 # 当前头文件路径
INCDIR	:= $(shell pwd) 

# C预处理器的flag，flag就是编译器可选的选项   不用标准库；不用标准头文件；指定自己的头文件目录
CPPFLAGS	:= -nostdlib -nostdinc -I$(INCDIR)/include
# C编译器的flag               给警告信息；优化等级；编译链接是用自己的东西；
CFLAGS		:= -Wall -O2 -fno-builtin         

#导出这些变量到全局，其实就是给子文件夹下面的Makefile使用
export CC LD OBJCOPY OBJDUMP AR CPPFLAGS CFLAGS


objs := start.o sdram_init.o led.o uart.o main.o
#objs += clock.o

#父Makefile依赖子Makefile,会进入lib目录下
objs += lib/libc.a



uart.bin: $(objs)
	$(LD) -Tlink.lds -o uart.elf $^
	$(OBJCOPY) -O binary uart.elf uart.bin
	$(OBJDUMP) -D uart.elf > uart_elf.dis
	gcc mkv210_image.c -o mkx210
	./mkx210 uart.bin 210.bin

#不依赖任何目标,每次都make
lib/libc.a:
	cd lib;	make;	cd ..
	
%.o : %.S
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $< -c

%.o : %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $< -c

clean:
	rm *.o *.elf *.bin *.dis mkx210 -f
	cd lib; make clean; cd ..

	
	