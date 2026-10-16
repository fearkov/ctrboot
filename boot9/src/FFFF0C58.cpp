#pragma arm
#include "types.h"

void FUN_FFFF0C58(void)
{
    register u32 control __asm("cp15:0:c1:c0:0");
    register u32 invalidate_icache __asm("cp15:0:c7:c5:0");
    register u32 invalidate_dcache __asm("cp15:0:c7:c6:0");
    register u32 drain_write_buffer __asm("cp15:0:c7:c10:4");

    control = 0x52078;
    invalidate_icache = 0;
    invalidate_dcache = 0;
    drain_write_buffer = 0;
}
