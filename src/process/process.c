#include <stdio.h>
#include <stdlib.h>
#include "instruction.h"
#include "process.h"

Process* new_process( const char* name )
{
    Process* p = malloc( sizeof(Process) );

    *p = (Process) {
        .pid = 0,
        .ppid = 1, // Processo principal (simulador) invocou todos os outros
        .name = name,

        .state = READY,
        .instructions = NULL,
        .instructions_size = 0,
        .program_counter = 0,
        .priority = 1,

        .color = random_dark_color()
    };
    
    generate_instruction_set( &p->instructions, &p->instructions_size );

    return p;
}


void delete_process( Process** p )
{
    free( *p );
    *p = NULL;
}


Instruction fetch_next_instruction( Process* p )
{
    // Evita problemas
    if ( p->instructions == NULL || p->instructions_size == 0 )
        return NOOP;

    if ( p->program_counter >= p->instructions_size )
        return NOOP;
    
    return p->instructions[ p->program_counter ];
}


void draw_proc( Process* p, UI* canvas, int x, int y )
{
    // Plano de fundo
    draw_rect( canvas, 1, p->color, x, y, PROCESS_DRAW_WIDTH, PROCESS_DRAW_HEIGHT );
    
    // PID
    char pid[255];
    sprintf( pid, "PID: %d", p->pid );
    draw_text( canvas, pid, WHITE, x+6, y+8 );

    // Nome
    char name[255];
    sprintf( name, "%s", p->name );
    draw_text( canvas, name, WHITE, x+PROCESS_DRAW_WIDTH/2, y+8 );

    // Prioridade
    char priority[255];
    sprintf( priority, "Prioridade: %d", p->priority );
    draw_text( canvas, priority, WHITE, x+6, y+18 );

    // Estado
    SDL_Color state;
    switch (p->state)
    {
        case READY: state = GREEN; break;
        case RUNNING: state = YELLOW; break;
        case IO: state = RED; break;
        case TERMINATED:
        default: state = BLACK; break;
    }
    draw_rect( canvas, 1, state, x+PROCESS_DRAW_WIDTH-16, y, 16, 16 );
    draw_rect( canvas, 0, BLACK, x+PROCESS_DRAW_WIDTH-16, y, 16, 16 );

    // Instruções
    for ( uint32_t i=0; i<p->instructions_size; i++ )
    {
        int padding = 3;
        int margin = 2;
        int max_instructions = 15;
        int w = (PROCESS_DRAW_WIDTH - 2*padding - (max_instructions-1)*margin)/max_instructions;
        int h = PROCESS_DRAW_HEIGHT/3;
        int ix = x + i*w + padding + i*margin;
        int iy = y + PROCESS_DRAW_HEIGHT - padding - h;

        // Fundo da instrução
        draw_rect(
            canvas, 1,
            p->instructions[i] == CPU ? BLUE : RED,
            ix, iy,
            w, h
        );

        char iletter[2] = { get_instruction_str(p->instructions[i])[0], '\0' };

        // Sigla da instrução
        draw_text( canvas, iletter, WHITE, ix+2, iy+2 );

        // Borda da instrução
        draw_rect(
            canvas, 0,
            i == p->program_counter ? WHITE : BLACK,
            ix, iy,
            w, h
        );
    }
}


void print_proc( Process* p )
{
    printf( "PID: %d | #%d | %s %s (PPID: %d ) | PC: %d | Instr: ", p->pid, p->priority, get_state_str(p->state), p->name, p->ppid, p->program_counter );
    for ( uint32_t i=0; i<p->program_counter; i++ )
        printf( "%c", get_instruction_str( p->instructions[i] )[0] );
    printf( "!" );
    for ( uint32_t i=p->program_counter; i<p->instructions_size; i++ )
        printf( "%c", get_instruction_str( p->instructions[i] )[0] );
    printf("\n");
}


Instruction run( Process* p )
{
    Instruction i = fetch_next_instruction( p );
    ++p->program_counter;
    p->state = (i == CPU) ? RUNNING : (i == NOOP) ? READY : IO;
    return i;
}