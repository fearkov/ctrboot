#include "types.h"

extern u8 *DAT_FFF00198;
extern u32 DAT_FFF000A8;
extern u32 (*DAT_FFF000AC)(u8 *dst);
extern u32 DAT_FFF000B0;

extern "C" u32 FUN_FFFF3BD4(u8 *dst);
extern "C" void FUN_FFFF2E38(u32 a, u32 b);

void FUN_FFFF3900(u32 a, u32 b, u8 *src)
{
    DAT_FFF00198 = src;
    DAT_FFF000A8 = 0;
    DAT_FFF000AC = FUN_FFFF3BD4;
    DAT_FFF000B0 = 0;
    FUN_FFFF2E38(a, b);
}
