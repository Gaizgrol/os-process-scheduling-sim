#include "state.h"

const char* get_state_str( State s )
{
    switch (s)
    {
        case READY: return "READY";
        case RUNNING: return "RUNNING";
        case IO: return "WAITING";
        case TERMINATED: return "TERMINATED";
        default: return "UNKNOWN";
    }
}