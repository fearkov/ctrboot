// Built for space, like FUN_FFFF3EB8: -Otime would end the function with pop {r4, r5} and bx lr.
#pragma Ospace
#include "types.h"

struct Unk_10009000 {
    u32 unk00;
    u8 pad04[0x1c];
    u32 unk20;
    u32 unk24;
    u32 unk28;
    u32 unk2c;
};

extern volatile struct Unk_10009000 DAT_10009000;

void FUN_FFFF8A64(u32 mode, const u32 *data)
{
    DAT_10009000.unk00 = (DAT_10009000.unk00 & ~0x02800000) | (mode << 23);
    if (mode & 4) {
        DAT_10009000.unk20 = data[3];
        DAT_10009000.unk24 = data[2];
        DAT_10009000.unk28 = data[1];
        DAT_10009000.unk2c = data[0];
    } else {
        DAT_10009000.unk20 = data[0];
        DAT_10009000.unk24 = data[1];
        DAT_10009000.unk28 = data[2];
        DAT_10009000.unk2c = data[3];
    }
}
