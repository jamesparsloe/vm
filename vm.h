#ifndef VM_H
#define VM_H

#include "chunk.h"
#include "table.h"

#define STACK_MAX 256

typedef struct
{
    Chunk *chunk;
    uint8_t *ip;
    Value stack[STACK_MAX];
    Value *stack_top;
    Table globals;
    Table strings;
    Obj *objects;
} VM;

void push(Value value);
Value pop();

extern VM vm;

void vm_init();
void vm_free();

typedef enum
{
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR,
} InterpretResult;

InterpretResult interpret(const char *source);

#endif