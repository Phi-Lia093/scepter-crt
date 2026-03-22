# ============================================================================
# Makefile for C Runtime Library (libc.a)
# ============================================================================

# Compiler and tools
CC = gcc
AS = gcc
AR = ar
LD = gcc

# Compiler flags
CFLAGS = -c -ffreestanding -nostdlib -fno-builtin -fno-stack-protector \
          -fno-pie -mno-red-zone -O100 -Wall -Wextra -fno-pic -m32 -I ./include
ASFLAGS = -c -ffreestanding -nostdlib -fno-builtin -fno-stack-protector \
          -fno-pie -mno-red-zone -O100 -Wall -Wextra -fno-pic -m32 -I ./include
ARFLAGS = rcs
LDFLAGS = -T linker.ld -ffreestanding -nostdlib -fno-builtin -fno-stack-protector \
          -fno-pie -mno-red-zone -O100 -Wall -Wextra -fno-pic -m32

# Build directory
BUILD_DIR = build

# Output
LIBC = $(BUILD_DIR)/libc.a

# Source files
C_SOURCES = syscall.c
ASM_SOURCES = crt0.s

# Object files (in build directory)
C_OBJECTS = $(addprefix $(BUILD_DIR)/, $(C_SOURCES:.c=.o))
ASM_OBJECTS = $(addprefix $(BUILD_DIR)/, $(ASM_SOURCES:.s=.o))
ALL_OBJECTS = $(C_OBJECTS) $(ASM_OBJECTS)

# ============================================================================
# Build targets
# ============================================================================

.PHONY: all clean

all: $(LIBC)

# Create build directory if it doesn't exist
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(LIBC): $(BUILD_DIR) $(ALL_OBJECTS)
	@echo "  AR      $@"
	@$(AR) $(ARFLAGS) $@ $(ALL_OBJECTS)

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	@echo "  CC      $<"
	@$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: %.s | $(BUILD_DIR)
	@echo "  AS      $<"
	@$(AS) $(ASFLAGS) $< -o $@

clean:
	@echo "Cleaning crt build artifacts..."
	@rm -rf $(BUILD_DIR)
	@echo "✓ Clean complete"

# ============================================================================
# Helper target to build user programs
# ============================================================================

init: $(LIBC)
	@$(CC) $(CFLAGS) -c init.c -o $(BUILD_DIR)/init.o
	@$(LD) $(LDFLAGS) -o build/init $(BUILD_DIR)/crt0.o $(BUILD_DIR)/init.o $(LIBC)
	@$(CC) $(CFLAGS) -c sh.c -o $(BUILD_DIR)/sh.o
	@$(LD) $(LDFLAGS) -o build/sh $(BUILD_DIR)/crt0.o $(BUILD_DIR)/sh.o $(LIBC)

# ============================================================================
# Dependencies
# ============================================================================

$(BUILD_DIR)/syscall.o: syscall.c include/syscall.h
$(BUILD_DIR)/crt0.o: crt0.s
