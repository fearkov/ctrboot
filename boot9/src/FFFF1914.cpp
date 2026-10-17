#include "types.h"

extern "C" void FUN_FFFF1884(u32 index);

// The handler of interrupt 1: runs the handler registered for it.
void FUN_FFFF1914()
{
    FUN_FFFF1884(1);
}
