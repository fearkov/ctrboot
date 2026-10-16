#include "types.h"

struct Unk_10164000 {
    u8 unk0[4];
    volatile u32 unk4;
    u8 unk8[0x14];
    volatile u32 unk1C;
};
extern Unk_10164000 DAT_10164000;

struct Unk_FFFF34BC {
    u8 unk0[0x14];
    u32 *unk14;
};

extern "C" void FUN_FFFF3570(Unk_FFFF34BC *p);
extern "C" void FUN_FFFF355C(u32 *p);
extern "C" void FUN_FFFF35B0();

u32 FUN_FFFF34BC(Unk_FFFF34BC *p)
{
    while ((s32)DAT_10164000.unk4 < 0) {}
    FUN_FFFF3570(p);
    FUN_FFFF355C(p->unk14);
    FUN_FFFF35B0();
    return DAT_10164000.unk1C;
}
