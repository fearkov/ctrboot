#include "types.h"

extern u8 DAT_FFF00050[8];
extern volatile u16 DAT_10003000;
extern "C" void *FUN_FFFF25F0(void *dst, const void *src, u32 size);
extern "C" u32 FUN_FFFF1F38();
extern "C" u32 FUN_FFFF210C(u32 irq);
extern "C" void FUN_FFFF2128(u32 state);

u64 FUN_FFFF1F70()
{
    u32 state = FUN_FFFF1F38();
    u64 ticks;
    volatile u16 *reg = &DAT_10003000;
    const u8 *src = DAT_FFF00050;
    u64 counter = *reg;
    FUN_FFFF25F0(&ticks, src, 8);
    if (FUN_FFFF210C(8) != 0 && (counter & 0x8000) == 0) {
        ticks++;
    }
    ticks <<= 16;
    FUN_FFFF2128(state);
    return counter | ticks;
}
