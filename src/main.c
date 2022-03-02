#include <stdio.h>
#include "queue.h"
#include "scheduler.h"

void test1();
void test2();
void test3();

int main( int argc, char** argv )
{
    // test1();
    // test2();
    test3();

    return 0;
}

void test1()
{
    Proc_Queue* q = new_queue();

    Process* procs[4] = {
        new_process( 8319, 0, 5, "Salve" ),
        new_process( 4686, 0, 12, "Eae" ),
        new_process( 1290, 0, 3, "Tmj" ),
        new_process( 9437, 0, 10, "Mec" )
    };

    for ( uint8_t i=0; i<4; i++ )
        print_proc( procs[i] );

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
}

void test2()
{
    Scheduler* s = new_scheduler();

    proc_enqueue( s->cpu_high_priority_queue, &(Proc_Node){
        .actual = new_process( 123, 0, 5, "Salve" )
    });
    proc_enqueue( s->cpu_high_priority_queue, &(Proc_Node){
        .actual = new_process( 231, 0, 5, "Coe" )
    });
    proc_enqueue( s->cpu_low_priority_queue, &(Proc_Node){
        .actual = new_process( 312, 0, 5, "Menor" )
    });
    proc_enqueue( s->cpu_low_priority_queue, &(Proc_Node){
        .actual = new_process( 213, 0, 5, "Lek" )
    });
    proc_enqueue( s->cpu_high_priority_queue, &(Proc_Node){
        .actual = new_process( 321, 0, 5, "Eae" )
    });

    printf( "%s\n", ( s->cpu_running ) ? s->cpu_running->actual->name : "NULL" );

    cpu_fetch_next( s );

    printf( "%s\n", ( s->cpu_running ) ? s->cpu_running->actual->name : "NULL" );

    cpu_fetch_next( s );

    printf( "%s\n", ( s->cpu_running ) ? s->cpu_running->actual->name : "NULL" );

    cpu_fetch_next( s );

    printf( "%s\n", ( s->cpu_running ) ? s->cpu_running->actual->name : "NULL" );

    cpu_fetch_next( s );

    printf( "%s\n", ( s->cpu_running ) ? s->cpu_running->actual->name : "NULL" );

    cpu_fetch_next( s );

    printf( "%s\n", ( s->cpu_running ) ? s->cpu_running->actual->name : "NULL" );

    delete_scheduler( &s );
}

void test3()
{
    
}