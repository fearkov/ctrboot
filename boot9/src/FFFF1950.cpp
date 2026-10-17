#include "types.h"

extern "C" void FUN_FFFF1884(u32 index);

// Entry 7 of the ARM9 handler table that FUN_FFFF1764 fills in: runs the handler registered in slot 7.
void FUN_FFFF1950()
{
    FUN_FFFF1884(7);
}
