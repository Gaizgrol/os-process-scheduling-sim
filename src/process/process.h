#ifndef PROCESS_H
#define PROCESS_H

#include <stdint.h>
#include "instruction.h"
#include "state.h"

typedef struct Process
{
    uint32_t pid;
    const char* name;

    State state;
    Instruction* instructions;
    uint32_t instructions_size;
    uint32_t program_counter;
} Process;

// Construtor
Process* new_process( const char* name );
// Destrutor
void delete_process( Process** p );

// Lê a instrução apontada pelo program_counter.
// Retorna NOOP caso tenha finalizado
Instruction fetch_next_instruction( Process* p );
// Mostra informações gerais do processo
void print_proc( Process* p );
// "Executa" a próxima instrução do processo.
// Retorna NOOP caso tenha finalizado
Instruction run( Process* p );


#endif