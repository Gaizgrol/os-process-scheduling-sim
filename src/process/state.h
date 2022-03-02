#ifndef STATE_H
#define STATE_H

// Estado de execução do processo
typedef enum State
{
    READY, RUNNING, IO
} State;

// Busca a representação em "string" de um determinado estado
const char* get_state_str( State s );

#endif