#ifndef TABLE_H
#define TABLE_H

#include "node.h"
#include "renderer.h"

// "Tabela" de processos
typedef struct Proc_Table
{
    Proc_Node** procs;
    uint16_t proc_count;
    uint16_t proc_max_count;
} Proc_Table;

// Construtor
Proc_Table* new_table();
// Destrutor
void delete_table( Proc_Table** table );

void draw_table( Proc_Table* table, UI* canvas );
// Mostra a tabela de processos
void print_table( Proc_Table* table );

// Adiciona na tabela e devolve o nó correspondente ao novo processo
Proc_Node* table_add( Proc_Table* table, Process* proc );
// Encontra um processo com o PID fornecido. Caso não exista, NULL é retornado
Proc_Node* table_find( Proc_Table* table, uint32_t pid );
// Remove um processo da tabela e desreferencia todas suas informações
Proc_Node* table_remove( Proc_Table* table, uint32_t pid );

#endif