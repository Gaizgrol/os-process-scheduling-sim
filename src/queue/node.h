#ifndef NODE_H
#define NODE_H

#include "process.h"

// Estrutura usada internamente nas filas de prioridade de processos
typedef struct Proc_Node
{
    struct Proc_Node* prev;
    Process* actual;
    struct Proc_Node* next;
} Proc_Node;

Proc_Node new_node( Process* proc );

#endif