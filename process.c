#include <stdlib.h>
#include "process.h"

Process* new_process( uint32_t pid, State priority, char* name )
{
    Process* p = malloc( sizeof( Process ) );
    
    p->pid = pid;
    p->priority = priority;
    p->name = name;
    
    return p;
}

void delete_process( Process* p )
{
    free( p );
    p = NULL;
}