#include <stdio.h>
#include "process.h"

int main( int argc, char** argv )
{
    Process* p = new_process( 123, 0, "Salve" );
    print( *p );
    delete_process( &p );

    return 0;
}