CROSS_COMPILE ?= arm-none-eabi-
AS      := $(CROSS_COMPILE)as
CC      := $(CROSS_COMPILE)gcc
LD      := $(CROSS_COMPILE)ld
OBJCOPY := $(CROSS_COMPILE)objcopy

CFLAGS := -O2 -Wall -nostdlib -nostartfiles -ffreestanding \
          -mcpu=cortex-a7 -mfloat-abi=soft -Ikernel/headers

LDFLAGS := -T linker.ld -nostdlib

KERNEL_SRC := \
    kernel/kernel.c \
    kernel/src/io.c \
    kernel/src/mmu.c \
    kernel/src/exceptions/exception_handlers.c \
    kernel/src/syscalls/syscalls.c \
    kernel/src/peripherals/uart.c

KERNEL_OBJ := $(KERNEL_SRC:.c=.o) kernel/src/exceptions/exceptions.o start.o
USER_OBJ := user_space/user.o

TARGET := kernel.elf
BIN := kernel.img

all: $(BIN)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.S
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(KERNEL_OBJ) $(USER_OBJ) linker.ld
	$(LD) $(LDFLAGS) -o $@ $(KERNEL_OBJ) $(USER_OBJ)

$(BIN): $(TARGET)
	$(OBJCOPY) -O binary $< $@

clean:
	rm -f $(KERNEL_OBJ) $(USER_OBJ) $(TARGET) $(BIN)

