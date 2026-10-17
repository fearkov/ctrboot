#include "types.h"

struct Unk_FFFF30B8 {
    u32 unk00;
    u32 unk04;
    u32 unk08;
    u32 unk0C;
    u32 unk10;
};

struct Unk_FFF01728 {
    u8 unk00[8];
    u32 unk08;
    u8 pad0C[8];
    Unk_FFFF30B8 *unk14;
    Unk_FFFF30B8 unk18[12];
};
extern Unk_FFF01728 DAT_FFF01728;

struct Unk_FFF000E8 {
    u8 pad00[0x18];
    u32 unk18;
};
extern Unk_FFF000E8 DAT_FFF000E8;

struct Unk_FFF00628 {
    u8 pad00[0x18];
    u16 unk18;
};
extern Unk_FFF00628 DAT_FFF00628;

extern "C" void FUN_FFFFA6B0(u32 value);
extern "C" void FUN_FFFF30B8(Unk_FFFF30B8 *out, u32 a, u32 b, u32 c, u32 x, u32 y, u32 e, u32 f, u32 g, u32 h);

void FUN_FFFF9720(u32 value)
{
    Unk_FFF000E8 *g = &DAT_FFF000E8;
    if (g->unk18 == 0) {
        if (value != 0)
            FUN_FFFFA6B0(0x51D);
        Unk_FFF01728 *p = &DAT_FFF01728;
        p->unk08 = 0xFFFFFFFF;
        FUN_FFFF30B8(&p->unk18[0], 0, 0x05000000, 0x08000000, 0, 0x18, 0, 0, 0, 0);
        FUN_FFFF30B8(&p->unk18[1], 0, 0, 0x08000000, 0x18, 0, 0, 0, 0, 0);
        FUN_FFFF30B8(&p->unk18[4], 0, 0x07000000, 0x08000000, 0x18, 0, 0, 0, 0, 0);
        FUN_FFFF30B8(&p->unk18[7], 0, 0x01000000, 0x08000000, 0x1FFF, 0x3F, 0, 0, 0, 0);
        FUN_FFFF30B8(&p->unk18[8], 0, 0x04000000, 0x08000000, 0x657, 1, 0, 0, 0, 0);
        FUN_FFFF30B8(&p->unk18[2], 0, 0, 0x08000000, 0x910, 0, 0, 0, 0, 0);
        FUN_FFFF30B8(&p->unk18[5], 0, 0x07000000, 0x08000000, 0x910, 0, 0, 1, 0, 1);
        FUN_FFFF30B8(&p->unk18[9], 0, 0x04000000, 0x08000000, 0x8F8, 0x18, 0, 1, 0, 1);
        u32 b;
        if (DAT_FFF00628.unk18 != 0)
            b = 0;
        else
            b = 1;
        FUN_FFFF30B8(&p->unk18[3], 0, 0, 0, 0x18, 0, b, b, b, b);
        FUN_FFFF30B8(&p->unk18[6], 0, 0x07000000, 0, 0, 1, b, b, b, b);
        FUN_FFFF30B8(&p->unk18[10], 0, 0x01000000, 0, 0x657, 1, b, b, b, b);
        FUN_FFFF30B8(&p->unk18[11], 0x40000000, 0x01000000, 0, 0x21, 1, b, b, b, b);
        g->unk18 = 1;
    }
}
