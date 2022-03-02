#include <stdlib.h>
#include <stdio.h>
#include "queue.h"
#include "scheduler.h"

Scheduler* new_scheduler()
{
    Scheduler* sch = malloc( sizeof( Scheduler ) );
    
    *sch = (Scheduler)
    {
        .clock = 0,

        .proc_count = 0,
        .proc_max_count = UINT16_MAX,

        .cpu_high_priority_queue = new_queue(),
        .cpu_low_priority_queue = new_queue(),
        .cpu_running = NULL,
        .cpu_max_time_slice = 3,

        .io_disk_queue = new_queue(),
        .io_disk_running = NULL,
        .io_disk_duration = 8,

        .io_tape_queue = new_queue(),
        .io_tape_running = NULL,
        .io_tape_duration = 6,

        .io_printer_queue = new_queue(),
        .io_printer_running = NULL,
        .io_printer_duration = 14
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


void clock( Scheduler* sch )
{
    // #TODO...
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