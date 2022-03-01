#include <stddef.h>
#include "queue.h"

Proc_Queue new_queue()
{
    return (Proc_Queue) {
        .front = NULL,
        .tail = NULL
    };
}

void proc_enqueue( Proc_Queue* queue, Proc_Node* node )
{
    Proc_Node* last = queue->tail;

    // Se não estava em uma fila, limpamos referências para evitar problemas
    node->prev = NULL;
    node->next = NULL;
    
    // Atualizamos o último
    queue->tail = node;
    // Marcamos quem é o penúltimo (NULL a fila não tenha nenhum processo)
    node->next = last;


    // Se existia um último, agora ele é o penúltimo
    if ( last )
        last->prev = node;
}

Proc_Node* proc_dequeue( Proc_Queue* queue )
{
    Proc_Node* first = queue->front;

    // Ninguém na fila
    if ( !first )
        return NULL;
    
    // Segundo vira o primeiro (NULL caso só tenha um na fila)
    queue->front = first->prev;

    // Para o segundo, desreferencie o primeiro anterior e se torne primeiro
    if ( first->prev )
        first->prev->next = NULL;

    // Saiu da fila, não tem ninguém atrás nem na frente
    first->prev = NULL;
    first->next = NULL;

    return first;
}

void print( Proc_Queue* queue )
{

}