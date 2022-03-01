#include <stdio.h>
#include "queue.h"

void here( uint8_t i ) {
    printf( "Cheguei aqui: %d\n", i );
}

int main( int argc, char** argv )
{
    Proc_Queue* q = new_queue();

    Process* procs[4] = {
        new_process( 8319, 0, 5, "Salve" ),
        new_process( 4686, 0, 12, "Eae" ),
        new_process( 1290, 0, 3, "Tmj" ),
        new_process( 9437, 0, 10, "Mec" )
    };

    for ( uint8_t i=0; i<4; i++ )
        print( procs[i] );

    printf( "Adicionando na fila...\n" );

    for ( uint8_t i=0; i<4; i++ )
        proc_enqueue( q, new_node( procs[i] ) );

    queue_print( q );

    for ( uint8_t i=0; i<10; i++ )
    {
        printf( "Removendo da fila...\n" );
        Proc_Node* node = proc_dequeue( q );
        print_node( node );
        queue_print( q );
    }

    // Limpeza de memória
    printf( "Limpeza de memória...\n" );
    for ( uint8_t i=0; i<4; i++ )
    {
        Proc_Node* node = proc_dequeue( q );
        delete_process( &procs[i] );
        delete_node( &node );
    }
    delete_queue( &q );

    // Fim do programa
    printf( "Fim do teste!\n" );

    

    return 0;
}