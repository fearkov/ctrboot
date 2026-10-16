#include "types.h"

extern "C" u32 FUN_FFFF8940();
extern "C" void FUN_FFFF047C(const volatile void *fifo, void *dst, u32 size);
extern "C" void FUN_FFFF0540(const void *src, void *dst);

// The same as FUN_FFFFAFE0, as the callback FUN_FFFFA10C gives FUN_FFFFB00C.
void FUN_FFFFB05C(u32 dst)
{
    while (FUN_FFFF8940() != 0x10) {
    }
    FUN_FFFF047C((const volatile void *)0x1000900C, (void *)0x1000A080, 0x40);
    FUN_FFFF0540((const void *)0x1000A080, (void *)dst);
}
