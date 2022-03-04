#include <stdlib.h>
#include <stdio.h>
#include "queue.h"
#include "scheduler.h"

Scheduler* new_scheduler()
{
    Scheduler* sch = malloc( sizeof( Scheduler ) );
    
    *sch = (Scheduler)
    {
        .time_elapsed = 0,

        .proc_table = new_table(),

        .cpu_high_priority_queue = new_queue(),
        .cpu_low_priority_queue = new_queue(),
        .cpu_running = NULL,
        .cpu_running_time = 0,
        .cpu_max_time_slice = 2,

        .io_disk_queue = new_queue(),
        .io_disk_running = NULL,
        .io_disk_running_time = 0,
        .io_disk_duration = 4,

        .io_tape_queue = new_queue(),
        .io_tape_running = NULL,
        .io_tape_running_time = 0,
        .io_tape_duration = 5,

        .io_printer_queue = new_queue(),
        .io_printer_running = NULL,
        .io_printer_running_time = 0,
        .io_printer_duration = 6
    };

    return sch;
}


void delete_scheduler( Scheduler** sch )
{
    Scheduler* s = *sch;
    
    delete_queue( &s->cpu_high_priority_queue );
    delete_queue( &s->cpu_low_priority_queue );
    delete_queue( &s->io_disk_queue );
    delete_queue( &s->io_tape_queue );
    delete_queue( &s->io_printer_queue );
    
    free( s );
    *sch = NULL;
}


void add_proc( Scheduler* sch, Process* proc )
{
    Proc_Node* node = table_add( sch->proc_table, proc );
    if ( !node )
        return;

    proc_enqueue( sch->cpu_high_priority_queue, node, READY );
}


void clock( Scheduler* sch )
{
    sch->time_elapsed++;
    clock_cpu( sch );
    clock_disk( sch );
    clock_tape( sch );
    clock_printer( sch );
}


void clock_cpu( Scheduler* sch )
{
    Proc_Node* running = sch->cpu_running;

    // Ninguém rodando!
    if ( !running )
    {
        // Não há próximos candidatos, sai da rotina
        if ( !sch->cpu_high_priority_queue->front && !sch->cpu_low_priority_queue->front )
            return;
        // Zera o relógio e coloca o candidato para executar
        sch->cpu_running_time = 0;
        cpu_fetch_next( sch );
        running = sch->cpu_running;
    }

    // Verifica o tipo de instrução do candidato de execução
    Instruction next = fetch_next_instruction( running->actual );

    if ( next != CPU )
        running->actual->priority = -1;

    switch ( next )
    {
        case CPU:
            // Pode continuar execução:
            if ( sch->cpu_running_time < sch->cpu_max_time_slice )
            {
                run( running->actual );
                sch->cpu_running_time++;
                return;
            }
            // Estourou o tempo:
            proc_enqueue( sch->cpu_low_priority_queue, running, READY );
            running->actual->priority = 0;
        break;
        case DISK: proc_enqueue( sch->io_disk_queue, running, IO ); break;
        // Fita magnética
        case TAPE: proc_enqueue( sch->io_tape_queue, running, IO ); break;
        // Impressora
        case PRINTER: proc_enqueue( sch->io_printer_queue, running, IO ); break;
        // Próxima instrução não existe: programa finalizou
        default: running->actual->state = TERMINATED; break;
    }

    // Espaço para execução será buscado somente no próximo ciclo
    sch->cpu_running = NULL;
    sch->cpu_running_time = 0;
}


void clock_disk( Scheduler* sch )
{
    Proc_Node* running = sch->io_disk_running;

    // Ninguém rodando!
    if ( !running )
    {
        // Não há próximos candidatos, sai da rotina
        if ( !sch->io_disk_queue->front )
            return;
        // Zera o relógio, coloca o processo para iniciar o IO e sai da rotina
        sch->io_disk_running_time = 0;
        io_disk_fetch_next( sch );
        run( sch->io_disk_running->actual );
        // return;
    }

    if ( sch->io_disk_running_time == sch->io_disk_duration )
    {
        Instruction i = fetch_next_instruction( running->actual );

        if ( i != NOOP )
        {
            // Terminou o tempo de IO, volta para a fila de baixa prioridade
            running->actual->priority = 0;
            proc_enqueue( sch->cpu_low_priority_queue, running, READY );
        }
        else
            running->actual->state = TERMINATED;

        // Espaço para IO em disco fica aberto
        sch->io_disk_running = NULL;
        sch->io_disk_running_time = 0;
    }
    else
        // Tem alguém rodando!
        // Aumenta o tempo de IO
        sch->io_disk_running_time++;
}


void clock_tape( Scheduler* sch )
{
    Proc_Node* running = sch->io_tape_running;

    // Ninguém rodando!
    if ( !running )
    {
        // Não há próximos candidatos, sai da rotina
        if ( !sch->io_tape_queue->front )
            return;
        // Zera o relógio, coloca o processo para iniciar o IO e sai da rotina
        sch->io_tape_running_time = 0;
        io_tape_fetch_next( sch );
        run( sch->io_tape_running->actual );
        return;
    }

    if ( sch->io_tape_running_time == sch->io_tape_duration )
    {
        Instruction i = fetch_next_instruction( running->actual );

        if ( i != NOOP )
        {
            // Terminou o tempo de IO, volta para a fila de alta prioridade
            running->actual->priority = 1;
            proc_enqueue( sch->cpu_high_priority_queue, running, READY );
        }
        else
            running->actual->state = TERMINATED;

        // Espaço para IO em fita fica aberto
        sch->io_tape_running = NULL;
        sch->io_tape_running_time = 0;
    }
    else
        // Tem alguém rodando!
        // Aumenta o tempo de IO
        sch->io_tape_running_time++;
}


void clock_printer( Scheduler* sch )
{
    Proc_Node* running = sch->io_printer_running;

    // Ninguém rodando!
    if ( !running )
    {
        // Não há próximos candidatos, sai da rotina
        if ( !sch->io_printer_queue->front )
            return;
        // Zera o relógio, coloca o processo para iniciar o IO e sai da rotina
        sch->io_printer_running_time = 0;
        io_printer_fetch_next( sch );
        run( sch->io_printer_running->actual );
        return;
    }

    if ( sch->io_printer_running_time < sch->io_printer_duration )
    {
        Instruction i = fetch_next_instruction( running->actual );

        if ( i != NOOP )
        {
            // Terminou o tempo de IO, volta para a fila de alta prioridade
            running->actual->priority = 1;
            proc_enqueue( sch->cpu_high_priority_queue, running, READY );
        }
        else
            running->actual->state = TERMINATED;

        // Espaço para IO em fita fica aberto
        sch->io_printer_running = NULL;
        sch->io_printer_running_time = 0;
    }
    else
        // Tem alguém rodando!
        // Aumenta o tempo de IO
        sch->io_printer_running_time++;
}


void cpu_fetch_next( Scheduler* sch )
{
    Proc_Queue* q = sch->cpu_high_priority_queue;

    // Não há processos na fila de prioridade alta, então busque na de prioridade baixa
    if ( !q->front )
        q = sch->cpu_low_priority_queue;
    // Não há processos na fila de prioridade baixa
    if ( !q->front )
        return;

    // Algum processo de alguma fila foi encontrado e será executado
    sch->cpu_running = proc_dequeue( q );
}


void io_disk_fetch_next( Scheduler* sch )
{
    Proc_Queue* q = sch->io_disk_queue;

    // Não há processos esperando IO do disco
    if ( !q->front )
        return;

    // Há algum processo a ser executado
    sch->io_disk_running = proc_dequeue( q );
}


void io_tape_fetch_next( Scheduler* sch )
{
    Proc_Queue* q = sch->io_tape_queue;

    // Não há processos esperando IO da fita
    if ( !q->front )
        return;

    // Há algum processo a ser executado
    sch->io_tape_running = proc_dequeue( q );
}


void io_printer_fetch_next( Scheduler* sch )
{
    Proc_Queue* q = sch->io_printer_queue;

    // Não há processos esperando IO da impressora
    if ( !q->front )
        return;

    // Há algum processo a ser executado
    sch->io_printer_running = proc_dequeue( q );
}


// void kill_proc( Scheduler* sch, uint32_t pid );


void draw_counter( UI* canvas, int count, int max, int x, int y )
{
    float w = (float) NODE_DRAW_WIDTH / max, h = COUNTER_HEIGHT;
    for ( int i=0; i<max; i++ )
        draw_rect( canvas, 1, GRAY, x + i*w, y, w-1, h );

    for ( int i=0; i<count; i++ )
        draw_rect( canvas, 1, CYAN, x + i*w + 1, y+1, w-2, h-2 );
}


void draw_scheduler( Scheduler* sch, UI* canvas )
{
    // Desenha os processos na tabela
    draw_table( sch->proc_table, canvas );

    // Desenha as filas de processos
    int margin = 16;
    int w = PROCESS_DRAW_WIDTH+2*margin+NODE_DRAW_WIDTH;
    int h = margin+NODE_DRAW_HEIGHT;
    
    // Desculpa:

    // CPU bound
    draw_rect( canvas, 1, CYAN, PROCESS_DRAW_WIDTH+margin, h-NODE_DRAW_HEIGHT, NODE_DRAW_WIDTH, NODE_DRAW_HEIGHT );
    if ( sch->cpu_running ) draw_node( sch->cpu_running, canvas, PROCESS_DRAW_WIDTH+margin, h-NODE_DRAW_HEIGHT );
    draw_counter( canvas, sch->cpu_running_time, sch->cpu_max_time_slice, PROCESS_DRAW_WIDTH+margin, h-NODE_DRAW_HEIGHT-COUNTER_HEIGHT );
    draw_rect( canvas, 1, BLUE, w, h-NODE_DRAW_HEIGHT, WINDOW_WIDTH, NODE_DRAW_HEIGHT );
    draw_queue( sch->cpu_high_priority_queue, canvas, w, h-NODE_DRAW_HEIGHT );
    draw_text( canvas, "CPU Low Priority", WHITE, w, h-NODE_DRAW_HEIGHT-2*COUNTER_HEIGHT );
    draw_rect( canvas, 1, BLUE, w, h*2-NODE_DRAW_HEIGHT, WINDOW_WIDTH, NODE_DRAW_HEIGHT );
    draw_queue( sch->cpu_low_priority_queue, canvas, w, h*2-NODE_DRAW_HEIGHT );
    draw_text( canvas, "CPU High Priority", WHITE, w, h*2-NODE_DRAW_HEIGHT-2*COUNTER_HEIGHT );
    
    // IO bound
    draw_rect( canvas, 1, MAGENTA, PROCESS_DRAW_WIDTH+margin, h*4-NODE_DRAW_HEIGHT, NODE_DRAW_WIDTH, NODE_DRAW_HEIGHT );
    draw_counter( canvas, sch->io_disk_running_time, sch->io_disk_duration, PROCESS_DRAW_WIDTH+margin, h*4-NODE_DRAW_HEIGHT-COUNTER_HEIGHT );
    if ( sch->io_disk_running ) draw_node( sch->io_disk_running, canvas, PROCESS_DRAW_WIDTH+margin, h*4-NODE_DRAW_HEIGHT );
    draw_rect( canvas, 1, RED, w, h*4-NODE_DRAW_HEIGHT, WINDOW_WIDTH, NODE_DRAW_HEIGHT );
    draw_queue( sch->io_disk_queue, canvas, w, h*4-NODE_DRAW_HEIGHT );
    draw_text( canvas, "IO Disk Waiting", WHITE, w, h*4-NODE_DRAW_HEIGHT-2*COUNTER_HEIGHT );
    
    draw_rect( canvas, 1, MAGENTA, PROCESS_DRAW_WIDTH+margin, h*5-NODE_DRAW_HEIGHT, NODE_DRAW_WIDTH, NODE_DRAW_HEIGHT );
    draw_counter( canvas, sch->io_tape_running_time, sch->io_tape_duration, PROCESS_DRAW_WIDTH+margin, h*5-NODE_DRAW_HEIGHT-COUNTER_HEIGHT );
    if ( sch->io_tape_running ) draw_node( sch->io_tape_running, canvas, PROCESS_DRAW_WIDTH+margin, h*5-NODE_DRAW_HEIGHT );
    draw_rect( canvas, 1, RED, w, h*5-NODE_DRAW_HEIGHT, WINDOW_WIDTH, NODE_DRAW_HEIGHT );
    draw_queue( sch->io_tape_queue, canvas, w, h*5-NODE_DRAW_HEIGHT );
    draw_text( canvas, "IO Tape Waiting", WHITE, w, h*5-NODE_DRAW_HEIGHT-2*COUNTER_HEIGHT );
    
    draw_rect( canvas, 1, MAGENTA, PROCESS_DRAW_WIDTH+margin, h*6-NODE_DRAW_HEIGHT, NODE_DRAW_WIDTH, NODE_DRAW_HEIGHT );
    draw_counter( canvas, sch->io_printer_running_time, sch->io_printer_duration, PROCESS_DRAW_WIDTH+margin, h*6-NODE_DRAW_HEIGHT-COUNTER_HEIGHT );
    if ( sch->io_printer_running ) draw_node( sch->io_printer_running, canvas, PROCESS_DRAW_WIDTH+margin, h*6-NODE_DRAW_HEIGHT );
    draw_rect( canvas, 1, RED, w, h*6-NODE_DRAW_HEIGHT, WINDOW_WIDTH, NODE_DRAW_HEIGHT );
    draw_queue( sch->io_printer_queue, canvas, w, h*6-NODE_DRAW_HEIGHT );
    draw_text( canvas, "IO Printer Waiting", WHITE, w, h*6-NODE_DRAW_HEIGHT-2*COUNTER_HEIGHT );
}


void print_scheduler( Scheduler* sch )
{
    printf( ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n" );
    print_table( sch->proc_table );
    printf( "== CPU RUNNING ==\n" );
    if ( sch->cpu_running )
    {
        printf( "%d/%d\n", sch->cpu_running_time, sch->cpu_max_time_slice );
        print_proc( sch->cpu_running->actual );
    }
    else
        printf( "NULL\n" );
    printf( "== CPU HIGH QUEUE ==\n" );
    print_queue( sch->cpu_high_priority_queue );
    printf( "----\n" );
    printf( "== CPU LOW QUEUE==\n" );
    print_queue( sch->cpu_low_priority_queue );
    printf( "----\n" );
    printf( "== DISK WAITING ==\n" );
    if ( sch->io_disk_running )
    {
        printf( "%d/%d\n", sch->io_disk_running_time, sch->io_disk_duration );
        print_proc( sch->io_disk_running->actual );
    }
    else
        printf( "NULL\n" );
    printf( "== DISK QUEUE==\n" );
    print_queue( sch->io_disk_queue );
    printf( "----\n" );
    printf( "== TAPE WAITING ==\n" );
    if ( sch->io_tape_running )
    {
        printf( "%d/%d\n", sch->io_tape_running_time, sch->io_tape_duration );
        print_proc( sch->io_tape_running->actual );
    }
    else
        printf( "NULL\n" );
    printf( "== TAPE QUEUE==\n" );
    print_queue( sch->io_tape_queue );
    printf( "----\n" );
    printf( "== PRINTER WAITING ==\n" );
    if ( sch->io_printer_running )
    {
        printf( "%d/%d\n", sch->io_printer_running_time, sch->io_printer_duration );
        print_proc( sch->io_printer_running->actual );
    }
    else
        printf( "NULL\n" );
    printf( "== PRINTER QUEUE==\n" );
    print_queue( sch->io_printer_queue );
    printf( "----\n" );
    printf( "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n" );
}