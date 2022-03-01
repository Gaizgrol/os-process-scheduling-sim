#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdint.h>
#include "queue.h"

typedef struct Scheduler
{
    uint16_t proc_max_count;
    uint16_t proc_count;
    uint16_t proc_max_time_slice;

    Proc_Queue* cpu_high_priority_queue;
    Proc_Queue* cpu_low_priority_queue;

    Proc_Queue* io_disk_queue;
    uint8_t io_disk_duration;

    Proc_Queue* io_tape_queue;
    uint8_t io_tape_duration;
    
    Proc_Queue* io_printer_queue;
    uint8_t io_printer_duration;
} Scheduler;

Scheduler* new_scheduler();
void delete_scheduler( Scheduler** sch );

#endif