#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"
#include "renderer.h"
#include "scheduler.h"


int main( int argc, char** argv )
{
    // Desenha a tela preta
    UI* canvas = new_ui();
    clear( canvas );
    refresh( canvas );

    Scheduler* s = new_scheduler();

    char cmd[255];
    int i=0;

    do
    {
        // Limpa a tela
        clear( canvas );

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
            print_scheduler( s );
        }

        // Desenha os processos
        for ( uint16_t i=0; i<s->proc_table->proc_count; i++ )
        {
            draw_proc( s->proc_table->procs[i]->actual, canvas, WINDOW_WIDTH-PROCESS_DRAW_WIDTH, (PROCESS_DRAW_HEIGHT+1)*i );
        }

        // Atualiza a tela
        refresh( canvas );
    } while ( strcmp( cmd, "s" ) != 0 );

    delete_ui( &canvas );

    return 0;
}
