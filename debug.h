#ifndef DEBUG_H
#define DEBUG_H

#include "chunk.h"

void chunk_disassemble(Chunk *chunk, const char *name);
int disassemble_instruction(Chunk *chunk, int offset);

#endif