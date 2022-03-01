#include <stdlib.h>
#include "queue.h"
#include "scheduler.h"

Scheduler* new_scheduler()
{
    Scheduler* sch = malloc( sizeof( Scheduler ) );
    
    *sch = (Scheduler)
    {
        .proc_max_count = UINT16_MAX,
        .proc_count = 0,
        .proc_max_time_slice = 3,

        .cpu_high_priority_queue = new_queue(),
        .cpu_low_priority_queue = new_queue(),

        .io_disk_queue = new_queue(),
        .io_disk_duration = 8,

        .io_tape_queue = new_queue(),
        .io_tape_duration = 6,

        .io_printer_queue = new_queue(),
        .io_printer_duration = 14
    };

    return sch;
}

void delete_scheduler( Scheduler** sch )
{
    free( *sch );
    *sch = NULL;
}