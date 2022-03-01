#ifndef PROCESS_H
#define PROCESS_H

#include <stdint.h>
#include "state.h"

typedef struct Process
{
    uint32_t pid;
    uint32_t cpu_burst_time;
    uint8_t priority;
    State state;
    const char* name;
} Process;

// Construtor
Process* new_process( uint32_t pid, uint8_t priority, uint32_t burst_time, const char* name );
// Destrutor
void delete_process( Process** p );

// Mostra informações gerais do processo
void print( Process* p );

#endif