#ifndef NODE_H
#define NODE_H

#include "process.h"

// Estrutura usada internamente nas filas de processos como uma lista
// duplamente conectada
typedef struct Proc_Node
{
    struct Proc_Node* prev;
    Process* actual;
    struct Proc_Node* next;
} Proc_Node;

Proc_Node new_node( Process* proc );

#endif