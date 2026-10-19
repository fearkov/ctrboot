#include "types.h"

extern volatile u32 DAT_17E01100[];

extern "C" u32 FUN_00011AC4();
extern "C" u32 FUN_00011AD8(u32 mask);
extern "C" void *FUN_00013254(void *dst, const void *src, u32 size);

void FUN_00012528(u32 *out)
{
    u32 saved[4];
    u32 state = FUN_00011AC4();
    FUN_00013254(saved, (const void *)DAT_17E01100, 16);
    DAT_17E01100[0x23] = DAT_17E01100[0x22] = DAT_17E01100[0x21] = DAT_17E01100[0x20] = 0xFFFFFFFF;
    FUN_00011AD8(state);
    FUN_00013254(out, saved, 16);
}
