#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "scheduler.h"

void test1();
void test2();
void test3();
void test4();

int main( int argc, char** argv )
{
    // test1();
    // test2();
    // test3();
    // test4();

    Scheduler* s = new_scheduler();

    char cmd[255];
    int i=0;

    do
    {
        printf("Aguardando comando (a: adicionar processo, c: clock, s: sair)...\n");
        scanf( "%s", cmd );

        if ( strcmp( cmd, "c" ) == 0 )
        {
            clock( s );
            printf( "Clock realizado!\n" );
            print_scheduler( s );
        } else if ( strcmp( cmd, "a" ) == 0 )
        {
            char* name = malloc( sizeof(char) * 17 );
            sprintf( name, "Processo #%d", i++ );

            Process* p = new_process( name );
            print_proc( p );
            add_proc( s, p );
        }
    } while ( strcmp( cmd, "s" ) != 0 );

    return 0;
}
