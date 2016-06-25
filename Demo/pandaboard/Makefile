NAME = FreeRTOSDemo

TOOLCHAIN = arm-none-eabi-
CC = $(TOOLCHAIN)gcc
CXX = $(TOOLCHAIN)g++
AS = $(TOOLCHAIN)as
LD = $(TOOLCHAIN)ld
OBJCOPY = $(TOOLCHAIN)objcopy
AR = $(TOOLCHAIN)ar

DEFINES = 

LIBS = 

SOURCE_DIR = ../..
BUILD_DIR = obj

C_OPTS =	-I. \
			-I"$(SOURCE_DIR)/Demo" \
			-I"$(SOURCE_DIR)/Demo/Common/include" \
			-I"$(SOURCE_DIR)/Source/include" \
			-I"$(SOURCE_DIR)/Source/portable/cortex-a9" \
			-std=c99 \
			-O3 \
			-Wall \
			-Werror \
			-fmessage-length=0 \
			-mcpu=cortex-a9

C_FILES =	Source/croutine.c \
			Source/list.c \
			Source/queue.c \
			Source/tasks.c \
			Source/timers.c \
			Source/portable/cortex-a9/port.c \
			Source/portable/MemMang/heap_2.c \
			Demo/pandaboard/main.c \
			Demo/pandaboard/omap4_uart.c \
			Demo/pandaboard/pl031_rtc.c \
			Demo/pandaboard/printf-stdarg.c \
			Demo/pandaboard/serial.c \
			Demo/pandaboard/sp804_timer.c \
			Demo/pandaboard/BlockQ.c \
			Demo/pandaboard/blocktim.c \
			Demo/pandaboard/comtest.c \
			Demo/pandaboard/countsem.c \
			Demo/pandaboard/dynamic.c \
			Demo/pandaboard/GenQTest.c \
			Demo/pandaboard/integer.c \
			Demo/pandaboard/PollQ.c \
			Demo/pandaboard/QPeek.c \
			Demo/pandaboard/recmutex.c \
			Demo/pandaboard/nostdlib.c \
			Demo/pandaboard/semtest.c
			
#						Demo/pandaboard/flop.c \

S_FILES =	Demo/pandaboard/startup.S

C_OBJS = $(C_FILES:%.c=$(BUILD_DIR)/%.o)

S_OBJS = $(S_FILES:%.S=$(BUILD_DIR)/%.o)

ALL_CFLAGS = $(C_OPTS) $(DEFINES) $(CFLAGS)
ALL_LDFLAGS = $(LD_FLAGS) -T plain.ld

AUTODEPENDENCY_CFLAGS=-MMD -MF$(@:.o=.d) -MT$@


all: $(NAME).uimg

clean:
	rm -rf $(BUILD_DIR) $(NAME).elf $(NAME).bin $(NAME).uimg

upload: $(NAME).bin
	expect \
	-c 'set timeout -1' \
	-c 'spawn cu -l /dev/ttyUSB0 -s 115200' \
	-c 'expect "autoboot:"' \
	-c 'sleep 0.1' \
	-c 'send "\r"' \
	-c 'expect "Panda #"' \
	-c 'sleep 0.1' \
	-c 'send "loady 0x80000000\r"' \
	-c 'sleep 0.1'
	sz --ymodem $(NAME).bin </dev/ttyUSB0 >/dev/ttyUSB0
	expect \
	-c 'set timeout -1' \
	-c 'spawn cu -l /dev/ttyUSB0 -s 115200' \
	-c 'send "\r"' \
	-c 'expect "Panda #"' \
	-c 'sleep 0.1' \
	-c 'send "go 0x80000000\r"' \
	-c 'expect "!!!!"'

$(NAME).uimg: $(NAME).bin
	mkimage -A arm -O linux -T kernel -C none -a 0x80800000 -e 0x80800000 \
	-d $(NAME).bin -n FreeRTOS $(NAME).uimg

$(NAME).bin: $(NAME).elf
	$(OBJCOPY) -O binary $(NAME).elf $(NAME).bin

$(NAME).elf: $(C_OBJS) $(S_OBJS)
	$(LD) $(ALL_LDFLAGS) -o $@ $^ $(LIBS)

.SUFFIXES: .o .c

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(ALL_CFLAGS) $(AUTODEPENDENCY_CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.S
	@mkdir -p $(dir $@)
	$(CC) $(ALL_CFLAGS) $(AUTODEPENDENCY_CFLAGS) -c $< -o $@

-include $(C_OBJS:.o=.d)

