#pragma arm
#include "types.h"

void FUN_FFFF096C(void)
{
    register u32 drain_write_buffer __asm("cp15:0:c7:c10:4");
    drain_write_buffer = 0;
}
