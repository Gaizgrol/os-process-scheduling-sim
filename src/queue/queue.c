#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "node.h"
#include "queue.h"

Proc_Queue* new_queue()
{
    Proc_Queue* queue = malloc( sizeof( Proc_Queue ) );
    
    *queue = (Proc_Queue) {
        .front = NULL,
        .tail = NULL
    };

    return queue; 
}


void delete_queue( Proc_Queue** queue )
{
    free( *queue );
    *queue = NULL;
}


void proc_enqueue( Proc_Queue* queue, Proc_Node* node )
{
    // "Limpa" o nó para evitar referências mortas
    node->next = NULL;
    node->prev = NULL;

    // Caso não tenha nenhum elemento, atualiza a estrutura e sai da rotina.
    // Senão, continue com o caso normal
    if ( !queue->front && !queue->tail )
    {
        queue->front = node;
        queue->tail = node;
        return;
    }

    // Vai para trás do último da fila
    queue->tail->prev = node;
    node->next = queue->tail;

    // E agora a última posição atualizada é o nó atual
    queue->tail = node;
}


Proc_Node* proc_dequeue( Proc_Queue* queue )
{
    // Nenhum elemento
    if ( !queue->front )
        return NULL;
    
    // Um elemento
    if ( queue->front->actual == queue->tail->actual )
    {
        Proc_Node* last = queue->front;
        queue->front = NULL;
        queue->tail = NULL;
        return last;
    }

    Proc_Node* old_first = queue->front;

    // O primeiro saiu, então o segundo vira o primeiro
    queue->front = old_first->prev;
    queue->front->next = NULL;

    // "Limpa" o nó para evitar referências mortas
    old_first->next = NULL;
    old_first->prev = NULL;

    return old_first;
}


void queue_print( Proc_Queue* queue )
{
    Proc_Node* node = queue->front;   
    while ( node )
    {
        print_node( node );
        printf("\n");
        node = node->prev;
    }
}