# Copyright 2013, Jernej Kovacic
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.


#
# Type "make help" for more details.
#


# Version 2014-05.28 of the Sourcery toolchain is used as a build tool.
# See comments in "setenv.sh" for more details about downloading it
# and setting the appropriate environment variables.

TOOLCHAIN = arm-none-eabi-
CC = $(TOOLCHAIN)gcc
CXX = $(TOOLCHAIN)g++
AS = $(TOOLCHAIN)as
LD = $(TOOLCHAIN)ld
OBJCOPY = $(TOOLCHAIN)objcopy
AR = $(TOOLCHAIN)ar

C_OPTS =	-I. \
			-I"$(SOURCE_DIR)/Demo" \
			-I"$(SOURCE_DIR)/Demo/Common/include" \
			-I"$(SOURCE_DIR)/Source/include" \
			-I"$(SOURCE_DIR)/Source/portable/arm926ej/" \
			-std=c99 \
			-O3 \
			-Wall -Wextra -Werror\
			-fmessage-length=0 \
			-mcpu=arm926ej-s

# Object files to be linked into an application
# Due to a large number, the .o files are arranged into logical groups:


BUILD_DIR = obj
SOURCE_DIR = ../..

S_FILES = Demo/versatilepb/startup.s

C_FILES =   Demo/versatilepb/main.c \
			Demo/versatilepb/init.c \
			Demo/versatilepb/print.c \
			Demo/versatilepb/receive.c \
			Demo/versatilepb/nostdlib.c \
			Demo/versatilepb/timer.c \
			Demo/versatilepb/interrupt.c \
			Demo/versatilepb/uart.c \
			Source/portable/MemMang/heap_1.c \
			Source/list.c \
			Source/queue.c \
			Source/tasks.c \
			Source/portable/arm926ej/port.c \
			Source/portable/arm926ej/portISR.c


C_OBJS = $(C_FILES:%.c=$(BUILD_DIR)/%.o)

S_OBJS = $(S_FILES:%.s=$(BUILD_DIR)/%.o)

ALL_CFLAGS = $(C_OPTS) $(DEFINES) $(CFLAGS)
ALL_LDFLAGS = $(LD_FLAGS) -T qemu.ld

ELF_IMAGE = image.elf
TARGET = image.bin

# Include paths to be passed to $(CC) where necessary
INC_FREERTOS = $(FREERTOS_SRC)include/
INC_DRIVERS = $(DRIVERS_SRC)include/


#
# Make rules:
#

all : $(TARGET)

rebuild : clean all

#$(TARGET) : $(OBJDIR) $(ELF_IMAGE)
#	$(OBJCOPY) -O binary $(word 2,$^) $@

$(TARGET) : $(ELF_IMAGE)
	$(OBJCOPY) -O binary $(ELF_IMAGE) $(TARGET)

$(BUILD_DIR) :
	mkdir -p $@

#$(ELF_IMAGE) : $(OBJS) $(LINKER_SCRIPT)
#	$(LD) -nostdlib -L $(OBJDIR) -T $(LINKER_SCRIPT) $(OBJS) $(OFLAG) $@

$(ELF_IMAGE) : $(C_OBJS) $(S_OBJS)
	$(LD) $(ALL_LDFLAGS) -o $@ $^ $(LIBS)
	
debug : _debug_flags all

debug_rebuild : _debug_flags rebuild

_debug_flags :
	$(eval CFLAGS += $(DEB_FLAG))

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(ALL_CFLAGS) $(AUTODEPENDENCY_CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.s
	@mkdir -p $(dir $@)
	$(CC) $(ALL_CFLAGS) $(AUTODEPENDENCY_CFLAGS) -c $< -o $@


# Cleanup directives:

clean_obj :
	$(RM) -r $(BUILD_DIR)

clean_intermediate : clean_obj
	$(RM) *.elf
	$(RM) *.img

clean : clean_intermediate
	$(RM) *.bin

# Short help instructions:

help :
	@echo
	@echo Valid targets:
	@echo - all: builds missing dependencies and creates the target image \'$(TARGET)\'.
	@echo - rebuild: rebuilds all dependencies and creates the target image \'$(TARGET)\'.
	@echo - debug: same as \'all\', also includes debugging symbols to \'$(ELF_IMAGE)\'.
	@echo - debug_rebuild: same as \'rebuild\', also includes debugging symbols to \'$(ELF_IMAGE)\'.
	@echo - clean_obj: deletes all object files, only keeps \'$(ELF_IMAGE)\' and \'$(TARGET)\'.
	@echo - clean_intermediate: deletes all intermediate binaries, only keeps the target image \'$(TARGET)\'.
	@echo - clean: deletes all intermediate binaries, incl. the target image \'$(TARGET)\'.
	@echo - help: displays these help instructions.
	@echo

.PHONY : all rebuild clean clean_obj clean_intermediate debug debug_rebuild _debug_flags help
