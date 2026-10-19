#pragma arm
#include "types.h"

void FUN_00011CE4(u32 asid)
{
    register u32 invalidate __asm("cp15:0:c8:c6:2");
    invalidate = asid & 0xFF;
}
