#include <stdlib.h>
#include "process.h"

Process* new_process( uint32_t pid, uint8_t priority, char* name )
{
    Process* p = malloc( sizeof( Process ) );
    
    p->pid = pid;
    p->priority = priority;
    p->state = READY;
    p->name = name;
    
    return p;
}

void delete_process( Process* p )
{
    free( p );
    p = NULL;
}