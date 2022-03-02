#include <stdio.h>
#include <stdlib.h>
#include "instruction.h"
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
        .priority = priority,
        .name = name,

        .state = READY,
        .instructions = NULL,
        .instructions_size = 0,
        .program_counter = 0
    };
    
    generate_instruction_set( &p->instructions, &p->instructions_size );

    return p;
}


void print_proc( Process* p )
{
    printf( "[%d] %s #%d: %s\n", p->pid, p->name, p->priority, get_state_str(p->state) );
    for ( uint32_t i=0; i<p->instructions_size; i++ )
        printf( "\t -%s\n", get_instruction_str( p->instructions[i] ) );
}