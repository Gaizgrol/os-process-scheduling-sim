#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "scheduler.h"


int main( int argc, char** argv )
{
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
            add_proc( s, p );
        }
    } while ( strcmp( cmd, "s" ) != 0 );

    return 0;
}
