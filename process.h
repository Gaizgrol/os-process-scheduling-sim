#include <stdint.h>
#include <stdbool.h>
#include <string.h>

typedef enum State
{
    READY, RUNNING, IO
} State;

typedef struct Process
{
    uint32_t pid;
    uint8_t priority;
    State state;
    char* name;
} Process;

void delete_process();
Process* new_process( uint32_t pid, uint8_t priority, char* name );