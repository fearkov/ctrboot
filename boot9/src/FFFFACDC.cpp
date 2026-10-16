#include "types.h"

extern "C" u16 *FUN_FFFF25F0(u16 *a, u8 *b, u32 n);
extern u8 DAT_FFF00240[];

void FUN_FFFFACDC(u16 *reg)
{
    FUN_FFFF25F0(reg, DAT_FFF00240, 0xc);
}
