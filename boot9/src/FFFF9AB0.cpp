#include "types.h"

struct Unk_080F8000 {
    u8 pad00[0x92];
    u16 unk92;
};
extern Unk_080F8000 DAT_080F8000;

struct Unk_FFF000E8 {
    u8 pad00[4];
    void (*unk4)(u32);
    void (*unk8)(u32);
    u8 pad0C[8];
    void (*unk14)();
    u8 pad18[8];
    u32 unk20;
    u8 pad24[4];
    u32 unk28;
};
extern Unk_FFF000E8 DAT_FFF000E8;

extern "C" void FUN_FFFF96B8();
extern "C" void FUN_FFFF9684();
extern "C" void FUN_FFFF9650();

void FUN_FFFF9AB0(u32 a)
{
    Unk_FFF000E8 *p = &DAT_FFF000E8;
    if (p->unk20 != 0) return;
    Unk_080F8000 *q = &DAT_080F8000;
    if (p->unk4) p->unk4(a);
    if (a == 0) FUN_FFFF96B8();
    else FUN_FFFF9684();
    p->unk8(a);
    FUN_FFFF9650();
    if (a == 0) {
        if (p->unk28 == 0 && p->unk14) p->unk14();
        if (q->unk92 != 0) return;
    }
    p->unk20 = 1;
}
