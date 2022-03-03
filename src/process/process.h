#ifndef PROCESS_H
#define PROCESS_H

#include <stdint.h>
#include "instruction.h"
#include "renderer.h"
#include "state.h"

typedef struct Process
{
    uint32_t pid;
    uint32_t ppid;
    const char* name;
    
    State state;
    Instruction* instructions;
    uint32_t instructions_size;
    uint32_t program_counter;
    int8_t priority; 
} Process;

static const int PROCESS_DRAW_WIDTH = 200;
static const int PROCESS_DRAW_HEIGHT = 32;

// Construtor
Process* new_process( const char* name );
// Destrutor
void delete_process( Process** p );

// Lê a instrução apontada pelo program_counter.
// Retorna NOOP caso tenha finalizado
Instruction fetch_next_instruction( Process* p );
// "Executa" a próxima instrução do processo.
// Retorna NOOP caso tenha finalizado
Instruction run( Process* p );

// Desenha o processo
void draw_proc( Process* p, UI* canvas, int x, int y );
// Mostra informações gerais do processo
void print_proc( Process* p );

#endif