#ifndef NODE_H
#define NODE_H

#include "process.h"
#include "renderer.h"

// Estrutura usada internamente nas filas de processos como uma lista
// duplamente conectada
typedef struct Proc_Node
{
    struct Proc_Node* prev;
    Process* actual;
    struct Proc_Node* next;
} Proc_Node;

static const int NODE_DRAW_WIDTH = 70;
static const int NODE_DRAW_HEIGHT = 70;
static const int NODE_ARROW_WIDTH = 24;
static const int NODE_ARROW_HEIGHT = 8;

// Construtor
Proc_Node* new_node( Process* proc );
// Destrutor
void delete_node( Proc_Node** node );

void draw_node( Proc_Node* node, UI* canvas, int x, int y );
// Mostra informações do nome do processo e seus vizinhos
void print_node( Proc_Node* node );

#endif