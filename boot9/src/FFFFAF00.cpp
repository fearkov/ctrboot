#pragma arm
#include "types.h"

extern "C" void FUN_FFFF81EC(const u32 *src, u32 *dst, u32 size);
extern "C" void FUN_FFFF8204(u32 value, u32 *dst, u32 size);

extern u32 DAT_FFFFE060[];
extern u32 DAT_FFF00000[];
extern u32 DAT_FFF00230[];
extern u32 DAT_FFF01AC0[];

void FUN_FFFFAF00()
{
    u32 *zi = DAT_FFF00230;
    u32 zeroDiff = (u32)DAT_FFF01AC0 - (u32)DAT_FFF00230;
    u32 *rw = DAT_FFF00000;
    u32 rwDiff = 0xFFF00230u - (u32)DAT_FFF00000;
    const u32 *src = DAT_FFFFE060;
    u32 zeroSize = (zeroDiff + 3) & ~3u;
    u32 copySize = (rwDiff + 3) & ~3u;
    if (src != DAT_FFF00000)
        FUN_FFFF81EC(src, rw, copySize);
    if (zeroSize != 0)
        FUN_FFFF8204(0, zi, zeroSize);
}
