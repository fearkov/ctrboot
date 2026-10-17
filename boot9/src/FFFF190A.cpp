#include "types.h"

extern "C" void FUN_FFFF1884(u32 index);

// The handler of interrupt 0: runs the handler registered for it.
void FUN_FFFF190A()
{
    FUN_FFFF1884(0);
}
