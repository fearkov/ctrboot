#include "types.h"

extern u8 DAT_FFFFD860[];
extern u8 DAT_FFFFDC60[];

extern "C" void FUN_FFFF9038(u32 *src, u32 size, const u8 *table);

void FUN_FFFF9014(u32 *src, u32 size)
{
    const u8 *table = *(volatile u8 *)0x10010010 ? DAT_FFFFDC60 : DAT_FFFFD860;
    FUN_FFFF9038(src, size, table);
}
