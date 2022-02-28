#ifndef QUEUE_H
#define QUEUE_H

#include <stdint.h>
#include "node.h"

typedef struct Proc_Queue
{
    Proc_Node* start;
    Proc_Node* end;
} Proc_Queue;

Proc_Queue new_queue();

void proc_enqueue( Proc_Queue* queue, Proc_Node node );
Proc_Node proc_dequeue( Proc_Queue* queue );

#endif