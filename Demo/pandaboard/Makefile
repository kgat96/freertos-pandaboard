NAME = u-boot

TOOLCHAIN = arm-none-eabi-
CC = $(TOOLCHAIN)gcc
CXX = $(TOOLCHAIN)g++
AS = $(TOOLCHAIN)as
LD = $(TOOLCHAIN)gcc
OBJCOPY = $(TOOLCHAIN)objcopy
AR = $(TOOLCHAIN)ar
NM = $(TOOLCHAIN)nm
STRIP = $(TOOLCHAIN)strip
OBJDUMP = $(TOOLCHAIN)objdump
DEFINES = 

LIBS = 

SOURCE_DIR = ../..
BUILD_DIR = obj

C_OPTS =	-I. \
			-I"$(SOURCE_DIR)/Demo" \
			-I"$(SOURCE_DIR)/Demo/Common/include" \
			-I"$(SOURCE_DIR)/Source/include" \
			-I"$(SOURCE_DIR)/Source/portable/armv7r" \
			-std=c99 -g -Wall -fmessage-length=0 \
			-mthumb -march=armv7-a
			
S_OPTS =	-I. \
			-I"$(SOURCE_DIR)/Demo" \
			-I"$(SOURCE_DIR)/Demo/Common/include" \
			-I"$(SOURCE_DIR)/Source/include" \
			-I"$(SOURCE_DIR)/Source/portable/armv7r" \
			-mthumb -D__ASSEMBLY__ -g -msoft-float -march=armv7-a

C_FILES =   Source/portable/armv7r/port.c \
			Demo/pandaboard/main.c

			#
			#Source/croutine.c \
			#Source/list.c \
			#Source/queue.c \
			#Source/tasks.c \
			#Source/timers.c \
			#Source/portable/MemMang/heap_2.c \

S_FILES = Demo/pandaboard/startup.S

C_OBJS = $(C_FILES:%.c=$(BUILD_DIR)/%.o)

S_OBJS = $(S_FILES:%.S=$(BUILD_DIR)/%.o)

ALL_CFLAGS = $(C_OPTS) $(DEFINES) $(CFLAGS)

ALL_LDFLAGS =	$(LD_FLAGS) \
				-nostartfiles -Wl,-T,ldscript.ld \
				-march=armv7-a 

AUTODEPENDENCY_CFLAGS=#-MMD -MF$(@:.o=.d) -MT$@

OBJDUMP_FLAGS += -S -d -t #-s

all: $(NAME).img

clean:
	rm -rf $(BUILD_DIR) $(NAME).elf $(NAME).bin $(NAME).uimg

$(NAME).img: $(NAME).bin $(NAME).lst
	mkimage -A arm -O linux -T kernel -C none -a 0x80800000 -e 0x80800000 \
	-d $(NAME).bin -n FreeRTOS $(NAME).img

$(NAME).bin: $(NAME).elf
	$(OBJCOPY) -O binary $(NAME).elf $(NAME).bin

$(NAME).elf: $(C_OBJS) $(S_OBJS)
	$(LD) $(ALL_LDFLAGS) -o $@ $^ $(LIBS)

$(NAME).lst: $(NAME).elf
	$(OBJDUMP) $(OBJDUMP_FLAGS) $< > $@

.SUFFIXES: .o .c

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(ALL_CFLAGS) $(AUTODEPENDENCY_CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.S
	@mkdir -p $(dir $@)
	$(CC) $(ALL_CFLAGS) $(AUTODEPENDENCY_CFLAGS) -c $< -o $@

-include $(C_OBJS:.o=.d)

