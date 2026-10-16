// Built for space like the other helpers of this ROM: the 16-byte local comes from pushing r0-r3 along with
// r4-r6 (what -Ospace does; -Otime allocates it with sub sp).
#pragma Ospace
#include "types.h"

extern "C" void FUN_FFFF0374(const void *src, void *dst, u32 size);
extern "C" void FUN_FFFF86C0(u32 mode, u32 *ctr, u64 value);
extern "C" void FUN_FFFF8A64(u32 mode, const u32 *ctr);

void FUN_FFFFA594(const void *src, u32 unused, u64 value)
{
    u32 ctr[4];
    FUN_FFFF0374(src, ctr, 0x10);
    FUN_FFFF86C0(5, ctr, value >> 4);
    FUN_FFFF8A64(5, ctr);
}
