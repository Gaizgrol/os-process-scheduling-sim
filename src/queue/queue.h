#ifndef QUEUE_H
#define QUEUE_H

#include "node.h"

// Fila de processos implementando uma lista duplamente conectada
typedef struct Proc_Queue
{
    Proc_Node* front;
    Proc_Node* tail;
} Proc_Queue;

Proc_Queue new_queue();

void proc_enqueue( Proc_Queue* queue, Proc_Node* node );
Proc_Node* proc_dequeue( Proc_Queue* queue );
void print( Proc_Queue* queue );

#endif