#pragma arm
#include "types.h"

void FUN_000113C0()
{
    register u32 r __asm("cp15:0:c7:c10:4");
    r = 0;
}
