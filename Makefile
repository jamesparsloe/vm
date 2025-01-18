CC = gcc
CFLAGS = -Wall
DEBUG_FLAGS = 
LDFLAGS = -lm
TARGET = vm

# Debug configuration
DEBUG_TARGET = vm-debug
DEBUG_CFLAGS = -g -O0 -DDEBUG_PRINT_CODE -DDEBUG_TRACE_EXECUTION

.PHONY: all clean debug

DEPS = chunk.h common.h compiler.h debug.h memory.h object.h scanner.h table.h value.h vm.h
OBJFILES = chunk.o compiler.o debug.o main.o memory.o object.o scanner.o table.o value.o vm.o

all: $(TARGET)

debug: DEBUG_FLAGS = $(DEBUG_CFLAGS)
debug: $(DEBUG_TARGET)

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -c -o $@ $<

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -o $@ $^ $(LDFLAGS)

$(DEBUG_TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET) $(DEBUG_TARGET) *~