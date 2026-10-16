#include "types.h"

struct Unk_10011000 {
    volatile u32 unk0;
    u8 pad04[0xC];
    volatile u32 unk10;
};
extern Unk_10011000 DAT_10011000;

struct Unk_FFF0064C {
    u8 pad00[0x14];
    u32 unk14;
    u32 unk18;
    u32 unk1C;
    u32 unk20;
    u8 pad24[0x30];
    u8 unk54[1];
};
extern Unk_FFF0064C DAT_FFF0064C;

struct Unk_FFF000E8 {
    u8 pad00[0x10];
    void (*unk10)(u32);
};
extern Unk_FFF000E8 DAT_FFF000E8;

extern "C" void FUN_FFFF8438(void *a, u32 *b, u32 *c);

void FUN_FFFF9A08(u32 a)
{
    DAT_FFF000E8.unk10(a);
    Unk_FFF0064C *p = &DAT_FFF0064C;
    Unk_10011000 *h = &DAT_10011000;
    p->unk14 = h->unk0;
    p->unk18 = h->unk10;
    p->unk20 = h->unk10;
    p->unk1C = h->unk0;
    FUN_FFFF8438(p->unk54, &p->unk14, &p->unk18);
    FUN_FFFF8438(p->unk54, &p->unk20, &p->unk1C);
}
