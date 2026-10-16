#include "types.h"

extern u8 *DAT_FFF00198;

extern "C" void FUN_FFFF047C(u8 *dst, const u8 *src, u32 size);

u32 FUN_FFFF3BD4(u8 *dst)
{
    FUN_FFFF047C(dst, DAT_FFF00198, 0x200);
    DAT_FFF00198 += 0x200;
    return 0;
}
