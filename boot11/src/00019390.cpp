#pragma arm
#include "types.h"

extern "C" void FUN_00018140(const u32 *src, u32 *dst, u32 size);
extern "C" void FUN_00018158(u32 value, u32 *dst, u32 size);

extern u32 DAT_0001D078[];
extern u32 DAT_1FFE8000[];
extern u32 DAT_1FFE8120[];
extern u32 DAT_1FFE8E60[];

void FUN_00019390()
{
    u32 *zi = DAT_1FFE8120;
    u32 zeroDiff = (u32)DAT_1FFE8E60 - (u32)DAT_1FFE8120;
    u32 *rw = DAT_1FFE8000;
    u32 rwDiff = 0x1FFE8120u - (u32)DAT_1FFE8000;
    const u32 *src = DAT_0001D078;
    u32 zeroSize = (zeroDiff + 3) & ~3u;
    u32 copySize = (rwDiff + 3) & ~3u;
    if (src != DAT_1FFE8000)
        FUN_00018140(src, rw, copySize);
    if (zeroSize != 0)
        FUN_00018158(0, zi, zeroSize);
}
