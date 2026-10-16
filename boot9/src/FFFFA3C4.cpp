#include "types.h"

extern "C" void FUN_FFFF0868(u32 start, s32 size);
extern "C" void FUN_FFFF3600(u32 addr, u32 size, u8 *out);

// Invalidates the cache lines of buf, then has FUN_FFFF3600 fill it with size bytes from offset + 0x400.
u32 FUN_FFFFA3C4(u8 *buf, u32 offset, u32 size)
{
    // computed before the call, as the dump keeps it in a register across the call
    u32 addr = offset + 0x400;
    FUN_FFFF0868((u32)buf, size);
    FUN_FFFF3600(addr, size, buf);
    return 1;
}
