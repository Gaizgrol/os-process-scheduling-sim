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


void draw_node( Proc_Node* node, UI* canvas, int x, int y )
{
    Process* p = node->actual;

    // Plano de fundo
    draw_rect( canvas, 1, p->color, x, y, NODE_DRAW_WIDTH, NODE_DRAW_HEIGHT );
    
    // PID
    char pid[255];
    sprintf( pid, "PID: %d", p->pid );
    draw_text( canvas, pid, WHITE, x+4, y+NODE_DRAW_HEIGHT/3 );

    // Nome
    char name[255];
    sprintf( name, "%s", p->name );
    draw_text( canvas, name, WHITE, x+4, y+((2.0f/3)*NODE_DRAW_HEIGHT) );

    // Anterior
    if ( node->prev )
    {
        // Meio da seta
        draw_line(
            canvas, WHITE,
            x+NODE_DRAW_WIDTH, y+NODE_DRAW_HEIGHT*(1.0f/3),
            x+NODE_DRAW_WIDTH+NODE_ARROW_WIDTH, y+NODE_DRAW_HEIGHT*(1.0f/3)
        );
        // Ponta de cima
        draw_line(
            canvas, WHITE,
            x+NODE_DRAW_WIDTH+NODE_ARROW_WIDTH, y+NODE_DRAW_HEIGHT*(1.0f/3),
            x+NODE_DRAW_WIDTH+NODE_ARROW_WIDTH-NODE_ARROW_HEIGHT, y+NODE_DRAW_HEIGHT*(1.0f/3)-NODE_ARROW_HEIGHT
        );
    }
    // Próximo
    if ( node->next )
    {
        // Meio da seta
        draw_line(
            canvas, WHITE,
            x, y+NODE_DRAW_HEIGHT*(2.0f/3),
            x-NODE_ARROW_WIDTH, y+NODE_DRAW_HEIGHT*(2.0f/3)
        );
        // Ponta de cima
        draw_line(
            canvas, WHITE,
            x-NODE_ARROW_WIDTH, y+NODE_DRAW_HEIGHT*(2.0f/3),
            x-NODE_ARROW_WIDTH+NODE_ARROW_HEIGHT, y+NODE_DRAW_HEIGHT*(2.0f/3)+NODE_ARROW_HEIGHT
        );
    }
}


void print_node( Proc_Node* node )
{
    if ( !node )
    {
        printf("NULL\n");
        return;
    }
    
    printf(
        "%s <= [ %s ] => %s",
        (node->next) ? node->next->actual->name : "NULL",
        node->actual->name,
        (node->prev) ? node->prev->actual->name : "NULL"
    );
}