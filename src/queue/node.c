#include <stddef.h>
#include "node.h"

Proc_Node new_node( Process* proc )
{
    return ( Proc_Node ) {
        .prev = NULL,
        .actual = proc,
        .next = NULL
    };
}