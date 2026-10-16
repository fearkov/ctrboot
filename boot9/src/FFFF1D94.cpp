#include "types.h"

extern "C" u32 FUN_FFFF1F38();
extern "C" void FUN_FFFF2128(u32 state);

// Stops one NDMA channel (clears the enable bit of its control register) with IRQs masked.
void FUN_FFFF1D94(u32 index)
{
    u32 state = FUN_FFFF1F38();
    volatile u32 *reg = (volatile u32 *)(0x1000201C + index * 0x1C);
    *reg &= 0x7FFFFFFF;
    // two dummy reads of the register after the write
    u32 readback0 = *reg;
    u32 readback1 = *reg;
    (void)readback0;
    (void)readback1;
    FUN_FFFF2128(state);
}
