#ifndef PROCESS_H
#define PROCESS_H

#include <stdint.h>

typedef enum State
{
    READY, RUNNING, IO
} State;

const char* get_state_str( State s );

typedef struct Process
{
    uint32_t pid;
    uint8_t priority;
    State state;
    const char* name;
} Process;

void delete_process( Process** p );
Process* new_process( uint32_t pid, uint8_t priority, const char* name );
void print( Process p );

#endif