BUILD:=../build
SRC:=.

ENTRYPOINT:=0x10000

CFLAGS:= -m32
CFLAGS+= -fno-builtin # 不需要 gcc 内置函数
CFLAGS+= -nostdinc # 不需要标准头文件
CFLAGS+= -fno-pic # 不需要位置无关代码 postion independt code
CFLAGS+= -fno-pie # 不需要位置无关代的可执行文件postion independt executable
CFLAGS+= -nostdlib # 不需要标准库
CFLAGS+= -fno-stack-protector # 不需要栈保护
CFLAGS+= $(strip ${CFLAGS})

DEBUG:= -g
INCLUDE:=-I$(SRC)/include

$(BUILD)/boot/%.bin: $(SRC)/boot/%.asm
	$(shell mkdir -p $(dir $@))
	echo "$(dir $@)"
	nasm -f bin $< -o $@ 

$(BUILD)/%.o: $(SRC)/%.asm
	$(shell mkdir -p $(dir $@))
	nasm -gdwarf -f elf32 $< -o $@

$(BUILD)/%.o: $(SRC)/%.c
	$(shell mkdir -p $(dir $@))
	gcc $(CFLAGS) $(DEBUG) $(INCLUDE) -c $< -o $@



$(BUILD)/kernel.bin:  \
	$(BUILD)/kernel/start.o \
	$(BUILD)/kernel/main.o \
	$(BUILD)/kernel/console.o \
	$(BUILD)/kernel/io.o \
	$(BUILD)/kernel/printk.o \
	$(BUILD)/lib/vsprintf.o \
	$(BUILD)/lib/string.o \
	$(BUILD)/kernel/assert.o\
	$(BUILD)/kernel/debug.o\
	$(BUILD)/kernel/global.o\
	

	$(shell mkdir -p $(dir $@))
	ld -m elf_i386 -static $^ -o $@ -Ttext $(ENTRYPOINT)

$(BUILD)/system.bin: $(BUILD)/kernel.bin
	objcopy -O binary $< $@

$(BUILD)/system.map: $(BUILD)/kernel.bin
	nm $< | sort > $@

$(BUILD)/master.img: \
    $(BUILD)/boot/boot.bin \
 	$(BUILD)/boot/loader.bin \
	$(BUILD)/system.bin \
	$(BUILD)/system.map \


	yes | bximage -q -hd=16 -func=create -sectsize=512 -imgmode=flat $@
	dd if=$(BUILD)/boot/boot.bin of=$@ bs=512 count=1 conv=notrunc
	dd if=$(BUILD)/boot/loader.bin of=$@ bs=512 count=4 seek=2 conv=notrunc
	dd if=$(BUILD)/system.bin of=$@ bs=512 count=200 seek=10 conv=notrunc  


test:$(BUILD)/master.img

.PHONY:clean
clean:
	rm -rf $(BUILD)

.PHONY:bochs
bochs: $(BUILD)/master.img
	bochs -q -f ../bochs/bochsrc

.PHONY:bochsg
bochsg: $(BUILD)/master.img
	bochs-gdb -q -f ../bochs/bochsrc.gdb

.PHONY:qemu
qemu:$(BUILD)/master.img
	qemu-system-i386 \
	-m 32M \
	-boot c \
	-hda $< 

.PHONY:qemug
qemug:$(BUILD)/master.img
	qemu-system-i386 \
	-m 32M \
	-boot c \
	-hda $< \
	-s -S 