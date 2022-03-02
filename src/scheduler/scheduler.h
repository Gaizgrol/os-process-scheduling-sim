#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdint.h>
#include "queue.h"

// Escalonador de processos do simulador
typedef struct Scheduler
{
    uint32_t clock;

    uint16_t proc_count;
    uint16_t proc_max_count;

    Proc_Queue* cpu_high_priority_queue;
    Proc_Queue* cpu_low_priority_queue;
    Proc_Node* cpu_running;
    uint8_t cpu_running_time;
    uint8_t cpu_max_time_slice;

    Proc_Queue* io_disk_queue;
    Proc_Node* io_disk_running;
    uint8_t io_disk_running_time;
    uint8_t io_disk_duration;

    Proc_Queue* io_tape_queue;
    Proc_Node* io_tape_running;
    uint8_t io_tape_running_time;
    uint8_t io_tape_duration;
    
    Proc_Queue* io_printer_queue;
    Proc_Node* io_printer_running;
    uint8_t io_printer_running_time;
    uint8_t io_printer_duration;
} Scheduler;

// Construtor
Scheduler* new_scheduler();
// Destrutor
void delete_scheduler( Scheduler** sch );

// Adiciona um processo ao escalonador
void add_proc( Scheduler* sch, Process* proc );
// Roda um ciclo de atualização completo no escalonador
void clock( Scheduler* sch );
// Atualiza a rotina de processos da CPU
void clock_cpu( Scheduler* sch );
// Atualiza a rotina de processos do disco
void clock_disk( Scheduler* sch );
// Atualiza a rotina de processos da fita
void clock_tape( Scheduler* sch );
// Atualiza a rotina de processos da impressora
void clock_printer( Scheduler* sch );
// Busca próximo processo a ser executado na CPU
void cpu_fetch_next( Scheduler* sch );
// Busca o próximo processo a utilizar IO de disco
void io_disk_fetch_next( Scheduler* sch );
// Busca o próximo processo a utilizar IO de fita magnética
void io_tape_fetch_next( Scheduler* sch );
// Busca o próximo processo a utilizar IO de impressora
void io_printer_fetch_next( Scheduler* sch );
// Mata um processo
void kill_proc( Scheduler* sch, uint32_t pid );
// Mostra informações do escalonador no terminal
void print_scheduler( Scheduler* sch );

#endif