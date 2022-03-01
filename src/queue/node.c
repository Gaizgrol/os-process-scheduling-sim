#include <stdio.h>
#include <stdlib.h>
#include "node.h"

Proc_Node* new_node( Process* proc )
{
    Proc_Node* node = malloc( sizeof( Proc_Node ) );
    
    *node = ( Proc_Node ) {
        .prev = NULL,
        .actual = proc,
        .next = NULL
    };

    return node;
}


void delete_node( Proc_Node** node )
{
    free( *node );
    *node = NULL;
}


void print_node( Proc_Node* node )
{
    if ( !node )
    {
        printf("NULL\n");
        return;
    }
    
    printf(
        "( %s <= [ %s ] => %s )",
        (node->next) ? node->next->actual->name : "NULL",
        node->actual->name,
        (node->prev) ? node->prev->actual->name : "NULL"
    );
}