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

// Construtor
Proc_Node* new_node( Process* proc );
// Destrutor
void delete_node( Proc_Node** node );

// Mostra informações do nome do processo e seus vizinhos
void print_node( Proc_Node* node );

#endif