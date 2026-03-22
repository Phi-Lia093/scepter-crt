# ============================================================================
# Makefile for C Runtime Library and Core Utilities
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

# Build directories
BUILD_DIR = build
ROOT_DIR = $(BUILD_DIR)/root
BIN_DIR = $(ROOT_DIR)/bin

# Output
LIBC = $(BUILD_DIR)/libc.a
CRT0 = $(BUILD_DIR)/crt0.o

# Source files
LIBC_C_SOURCES = libc/stdio/putchar.c \
                 libc/stdio/puts.c \
                 libc/stdio/printf.c \
                 libc/string/strlen.c \
                 libc/string/strcmp.c \
                 libc/string/strcpy.c \
                 libc/string/memset.c \
                 libc/string/memcpy.c \
                 libc/stdlib/atoi.c \
                 libc/stdlib/malloc.c \
                 libc/ctype/isdigit.c \
                 libc/ctype/isalpha.c \
                 libc/ctype/isspace.c \
                 libc/errno.c

SYSCALL_SOURCES = syscall.c
CRT0_SOURCE = libc/crt0.s

# Core utilities
COREUTILS = init sh test

# Object files (in build directory)
LIBC_OBJECTS = $(addprefix $(BUILD_DIR)/, $(LIBC_C_SOURCES:.c=.o))
SYSCALL_OBJECTS = $(addprefix $(BUILD_DIR)/, $(SYSCALL_SOURCES:.c=.o))
ALL_LIB_OBJECTS = $(LIBC_OBJECTS) $(SYSCALL_OBJECTS)

# Final executables in root filesystem
INIT_BIN = $(ROOT_DIR)/init
SH_BIN = $(BIN_DIR)/sh
TEST_BIN = $(BIN_DIR)/test

# ============================================================================
# Build targets
# ============================================================================

.PHONY: all clean install

all: $(LIBC) $(CRT0) $(COREUTILS)

# Create build directories
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BUILD_DIR)/libc/stdio
	@mkdir -p $(BUILD_DIR)/libc/string
	@mkdir -p $(BUILD_DIR)/libc/stdlib
	@mkdir -p $(BUILD_DIR)/libc/ctype
	@mkdir -p $(BUILD_DIR)/coreutil
	@mkdir -p $(ROOT_DIR)
	@mkdir -p $(BIN_DIR)

# Build libc.a
$(LIBC): $(BUILD_DIR) $(ALL_LIB_OBJECTS)
	@echo "  AR      $@"
	@$(AR) $(ARFLAGS) $@ $(ALL_LIB_OBJECTS)

# Build crt0.o
$(CRT0): $(CRT0_SOURCE) | $(BUILD_DIR)
	@echo "  AS      $<"
	@$(AS) $(ASFLAGS) $< -o $@

# Generic rules for object files
$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	@echo "  CC      $<"
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

# ============================================================================
# Core utilities
# ============================================================================

init: $(INIT_BIN)

$(INIT_BIN): $(CRT0) $(LIBC) coreutil/init.c | $(BUILD_DIR)
	@echo "  CC      coreutil/init.c"
	@$(CC) $(CFLAGS) -c coreutil/init.c -o $(BUILD_DIR)/coreutil/init.o
	@echo "  LD      $@"
	@$(LD) $(LDFLAGS) -o $@ $(CRT0) $(BUILD_DIR)/coreutil/init.o $(LIBC)
	@echo "✓ Built: $@"

sh: $(SH_BIN)

$(SH_BIN): $(CRT0) $(LIBC) coreutil/sh.c | $(BUILD_DIR)
	@echo "  CC      coreutil/sh.c"
	@$(CC) $(CFLAGS) -c coreutil/sh.c -o $(BUILD_DIR)/coreutil/sh.o
	@echo "  LD      $@"
	@$(LD) $(LDFLAGS) -o $@ $(CRT0) $(BUILD_DIR)/coreutil/sh.o $(LIBC)
	@echo "✓ Built: $@"

test: $(TEST_BIN)

$(TEST_BIN): $(CRT0) $(LIBC) coreutil/test.c | $(BUILD_DIR)
	@echo "  CC      coreutil/test.c"
	@$(CC) $(CFLAGS) -c coreutil/test.c -o $(BUILD_DIR)/coreutil/test.o
	@echo "  LD      $@"
	@$(LD) $(LDFLAGS) -o $@ $(CRT0) $(BUILD_DIR)/coreutil/test.o $(LIBC)
	@echo "✓ Built: $@"

# ============================================================================
# Install/clean
# ============================================================================

install:
	@echo "Root filesystem ready at: $(ROOT_DIR)"
	@echo "  /init       - Init process"
	@echo "  /bin/sh     - Shell"
	@echo "  /bin/test   - Test program"
	@tree -L 2 $(ROOT_DIR) 2>/dev/null || find $(ROOT_DIR) -type f

clean:
	@echo "Cleaning crt build artifacts..."
	@rm -rf $(BUILD_DIR)
	@echo "✓ Clean complete"

# ============================================================================
# Dependencies
# ============================================================================

$(BUILD_DIR)/syscall.o: syscall.c include/syscall.h