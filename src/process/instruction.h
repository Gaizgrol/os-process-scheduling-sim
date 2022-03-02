#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <stdint.h>

// Tipo de instrução do processo
typedef enum Instruction
{
    NOOP, CPU, DISK, TAPE, PRINTER
} Instruction;

// Gera instruções aleatórias e salva o conjunto de instruções no ponteiro
// apontado por ret_ins e seu tamanho no inteiro apontado por ret_size
void generate_instruction_set( Instruction** ret_ins, uint32_t* ret_size );
// Busca a representação em "string" de uma determinada instrução
const char* get_instruction_str( Instruction i );

#endif