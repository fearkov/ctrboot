#include "types.h"

struct Unk_10164000 {
    u8 unk0[4];
    volatile u32 unk4;
};
extern Unk_10164000 DAT_10164000;

struct Unk_FFFF4740 {
    u8 unk0[0x14];
    u32 *unk14;
};

extern "C" void FUN_FFFF3570(Unk_FFFF4740 *p);
extern "C" void FUN_FFFF355C(u32 *p);

void FUN_FFFF4740(Unk_FFFF4740 *p)
{
    while ((s32)DAT_10164000.unk4 < 0) {}
    FUN_FFFF3570(p);
    FUN_FFFF355C(p->unk14);
}
