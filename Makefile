CC = gcc
CFLAGS = -Wall
LDFLAGS = -lm

# Build directories
BUILD_DIR = build
RELEASE_DIR = $(BUILD_DIR)/release
DEBUG_DIR = $(BUILD_DIR)/debug


TARGET = vm

# Debug configuration 
DEBUG_CFLAGS = -g -O0 -DDEBUG_PRINT_CODE -DDEBUG_TRACE_EXECUTION

.PHONY: all clean debug dirs

DEPS = chunk.h common.h compiler.h debug.h memory.h object.h scanner.h table.h value.h vm.h
SRC = chunk.c compiler.c debug.c main.c memory.c object.c scanner.c table.c value.c vm.c

RELEASE_OBJFILES = $(addprefix $(RELEASE_DIR)/, $(SRC:.c=.o))
DEBUG_OBJFILES = $(addprefix $(DEBUG_DIR)/, $(SRC:.c=.o))

all: dirs $(RELEASE_DIR)/$(TARGET)

debug: dirs $(DEBUG_DIR)/$(TARGET)

dirs:
	@mkdir -p $(RELEASE_DIR) $(DEBUG_DIR)

$(RELEASE_DIR)/%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(DEBUG_DIR)/%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) $(DEBUG_CFLAGS) -c -o $@ $<

$(RELEASE_DIR)/$(TARGET): $(RELEASE_OBJFILES)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(DEBUG_DIR)/$(TARGET): $(DEBUG_OBJFILES)
	$(CC) $(CFLAGS) $(DEBUG_CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -rf $(BUILD_DIR)