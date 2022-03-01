#include <stdio.h>
#include <stdlib.h>
#include "process.h"

void delete_process( Process** p )
{
    free( *p );
    *p = NULL;
}


Process* new_process( uint32_t pid, uint8_t priority, uint32_t burst_time, const char* name )
{
    Process* p = malloc( sizeof(Process) );
    
    *p = (Process) {
        .pid = pid,
        .cpu_burst_time = burst_time,
        .priority = priority,
        .state = READY,
        .name = name
    };
    
    return p;
}


void print( Process* p )
{
    printf( "[%d] (%d) %s #%d: %s\n", p->pid, p->cpu_burst_time, p->name, p->priority, get_state_str(p->state) );
}