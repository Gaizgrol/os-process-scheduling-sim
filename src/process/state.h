#ifndef STATE_H
#define STATE_H

typedef enum State
{
    READY, RUNNING, IO
} State;

const char* get_state_str( State s );

#endif