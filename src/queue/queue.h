#ifndef QUEUE_H
#define QUEUE_H

#include "node.h"
#include "renderer.h"

// Fila de processos implementando uma lista duplamente conectada
typedef struct Proc_Queue
{
    Proc_Node* front;
    Proc_Node* tail;
} Proc_Queue;

// Construtor
Proc_Queue* new_queue();
// Destrutor
void delete_queue( Proc_Queue** queue );

// Remove um nó do início da fila
Proc_Node* proc_dequeue( Proc_Queue* queue );
// Adiciona um nó no final da fila
void proc_enqueue( Proc_Queue* queue, Proc_Node* node );

void draw_queue( Proc_Queue* queue, UI* canvas, int x, int y );
// Mostra as posições dos processos e quais são seus vizinhos
void print_queue( Proc_Queue* queue );

#endif