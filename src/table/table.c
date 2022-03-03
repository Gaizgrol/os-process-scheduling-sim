#include <stdio.h>
#include <stdlib.h>
#include "table.h"


Proc_Table* new_table()
{
    Proc_Table* table = malloc( sizeof( Proc_Table ) );
    
    *table = ( Proc_Table ) {
        .proc_count = 0,
        .proc_max_count = UINT16_MAX
    };
    Proc_Node** procs = malloc( sizeof( Proc_Node* ) * table->proc_max_count );
    table->procs = procs;

    return table;
}


void delete_table( Proc_Table** table )
{
    free( (*table)->procs );
    (*table)->procs = NULL;
    free( *table );
    *table = NULL;
}


void print_table( Proc_Table* table )
{
    printf( "Processos: %d/%d\n", table->proc_count, table->proc_max_count );
    for ( uint16_t i=0; i<table->proc_count; i++ )
        print_proc( table->procs[i]->actual );
    printf( "\n" );
}


Proc_Node* table_add( Proc_Table* table, Process* proc )
{
    if ( table->proc_count >= table->proc_max_count )
        return NULL;

    Proc_Node* node = new_node( proc );
    
    // PIDs únicos
    do {
        proc->pid = 100000 + rand() % 899999;
    } while( table_find( table, proc->pid ) != NULL );

    table->procs[table->proc_count++] = node;
    return node;
}


Proc_Node* table_find( Proc_Table* table, uint32_t pid )
{
    for ( uint16_t i=0; i<table->proc_count; i++ )
        if ( table->procs[i]->actual->pid == pid )
            return table->procs[i];
    return NULL;
}


Proc_Node* table_remove( Proc_Table* table, uint32_t pid )
{
    Proc_Node* node = table_find( table, pid );
    if ( !node )
        return NULL;
    
    Proc_Node* prev = node->prev;
    Proc_Node* next = node->next;

    // Remove de possíveis filas
    if ( prev )
        node->prev->next = next;
    if ( next )
        node->next->prev = prev;

    node->actual->state = TERMINATED;

    return node;
}