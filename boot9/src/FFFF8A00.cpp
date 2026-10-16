#include "types.h"

struct Unk_10009000
{
    u32 unk00;
    u16 unk04;
    u16 unk06;
};

extern volatile Unk_10009000 DAT_10009000;
extern u32 DAT_FFF000E0[2];

void FUN_FFFF8A00(u32 mode, u32 a, u32 b, u32 blkcnt, u32 blklen, u32 c, u32 d)
{
    DAT_FFF000E0[0] = c;
    DAT_FFF000E0[1] = d;
    if (mode == 0 || mode == 1) {
        DAT_10009000.unk04 = blkcnt;
    }
    DAT_10009000.unk06 = blklen;
    u32 v = DAT_10009000.unk00;
    v |= 0xC0000000;
    v = (v & ~0x38000000) | (mode << 27);
    v &= ~0x3000;
    v += 0x2000;
    v &= ~0xC000;
    v += 0x4000;
    v = (v & ~0x2800000) | (a << 23);
    v = (v & ~0x1400000) | (b << 22);
    DAT_10009000.unk00 = v;
}
