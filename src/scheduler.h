#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdint.h>
#include "process.h"

typedef struct Process_DLL_Node
{
    struct Process_DLL_Node* prev;
    Process* actual;
    struct Process_DLL_Node* next;
} Process_DLL_Node;

typedef struct Proc_DLL
{
    Process_DLL_Node start;
    Process_DLL_Node end;
} Proc_DLL;

typedef struct Scheduler
{
    uint16_t proc_max_count;
    uint8_t proc_max_time_slice;
    uint8_t io_disk_time;
    uint8_t io_tape_time;
    uint8_t io_printer_time;
} Scheduler;

#endif