#include "types.h"

extern "C" void FUN_FFFF0868(u32 start, s32 size);
extern "C" void FUN_FFFF470C(u32 a, s32 b, s32 c);

// Invalidates the cache lines of dst, then has FUN_FFFF470C fill it with size bytes from src + 0x7E00.
u32 FUN_FFFFA3E6(u32 dst, u32 src, u32 size)
{
    // computed before the call, as the dump keeps it in a register across the call
    u32 addr = src + 0x7E00;
    FUN_FFFF0868(dst, size);
    FUN_FFFF470C(addr, dst, size);
    return 1;
}
