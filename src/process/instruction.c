#include <stdlib.h>
#include <time.h>
#include "instruction.h"


void generate_instruction_set( Instruction** ret_ins, uint32_t* ret_size )
{
    struct timespec t;
    clock_gettime( CLOCK_MONOTONIC_RAW, &t );
    srand( (unsigned int) t.tv_nsec );

    // Entre 3 e 15 instruções
    int size = rand() % 12 + 3;
    
    *ret_size = size;
    *ret_ins = malloc( sizeof( Instruction ) * size );

    for ( int i=0; i<size; i++ )
    {
        int roll = rand() % 20;

        // 60% chance CPU, 40% chance IO
        (*ret_ins)[i] =
            ( roll < 12 ) ? CPU    //  0 - 11: 60%
            : ( roll < 16 ) ? DISK // 12 - 15: 20%
            : ( roll < 18 ) ? TAPE // 16 - 17: 10%
            :  PRINTER;            // 18 - 19: 10%
    }
}


const char* get_instruction_str( Instruction i )
{
    switch (i)
    {
        case NOOP: return "NOOP";
        case CPU: return "CPU";
        case DISK: return "DISK";
        case TAPE: return "TAPE";
        case PRINTER: return "PRINTER";
        default: return "UNKNOWN";
    }
}