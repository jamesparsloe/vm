CC = gcc
CFLAGS = -Wall
DEBUG_FLAGS = 
LDFLAGS = -lm
TARGET = vm

.PHONY: all clean

DEPS = chunk.h common.h compiler.h debug.h memory.h object.h scanner.h table.h value.h vm.h
OBJFILES = chunk.o compiler.o debug.o main.o memory.o object.o scanner.o table.o value.o vm.o

all: $(TARGET)

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -c -o $@ $<

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET) *~