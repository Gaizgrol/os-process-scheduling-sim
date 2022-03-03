#include <stdio.h>
#include <stdlib.h>
#include "instruction.h"
#include "process.h"

Process* new_process( const char* name )
{
    Process* p = malloc( sizeof(Process) );

    *p = (Process) {
        .pid = 0,
        .ppid = 100000 + rand() % 899999,
        .name = name,

        .state = READY,
        .instructions = NULL,
        .instructions_size = 0,
        .program_counter = 0,
        .priority = 1
    };
    
    generate_instruction_set( &p->instructions, &p->instructions_size );

    return p;
}


void delete_process( Process** p )
{
    free( *p );
    *p = NULL;
}


Instruction fetch_next_instruction( Process* p )
{
    // Evita problemas
    if ( p->instructions == NULL || p->instructions_size == 0 )
        return NOOP;

    if ( p->program_counter >= p->instructions_size )
        return NOOP;
    
    return p->instructions[ p->program_counter ];
}


void print_proc( Process* p )
{
    printf( "PID: %d | #%d | %s %s (PPID: %d ) | PC: %d | Instr: ", p->pid, p->priority, get_state_str(p->state), p->name, p->ppid, p->program_counter );
    for ( uint32_t i=p->program_counter; i<p->instructions_size; i++ )
        printf( "%c", get_instruction_str( p->instructions[i] )[0] );
    printf("\n");
}


Instruction run( Process* p )
{
    Instruction i = fetch_next_instruction( p );
    ++p->program_counter;
    p->state = (i == CPU) ? RUNNING : (i == NOOP) ? READY : IO;
    return i;
}