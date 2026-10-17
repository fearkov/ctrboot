#include "types.h"

struct Unk_FFF000E8 {
    u8 unk00[0x20];
    u32 unk20;
    u32 unk24;
};
extern Unk_FFF000E8 DAT_FFF000E8;

struct Unk_FFF00628 {
    u32 unk00;
    u8 unk04[0x14];
    u16 unk18;
};
extern Unk_FFF00628 DAT_FFF00628;

extern "C" void FUN_FFFF0198(u32 count);
extern "C" void FUN_FFFF9720(u32 value);
extern "C" void FUN_FFFF9B08();
extern "C" void FUN_FFFF47D0();
extern "C" void FUN_FFFF03A4(u32 value, void *dst, u32 size);
extern "C" void FUN_FFFF0868(u32 start, s32 size);
extern "C" void FUN_FFFF32A8(u32 a, u32 b, u32 c);
extern "C" u32 FUN_FFFFA670();
extern "C" void FUN_FFFF9AB0(u32 value);

// The same as FUN_FFFF46C0, inlined here.
static inline u32 IsNotSet()
{
    return ~*(volatile u8 *)0x10000010 & 1;
}

// Brings the card slot up once; returns whether the bit at 0x10000010 is still clear afterwards.
u32 FUN_FFFFA5EC()
{
    *(volatile u16 *)0x10000012 = 0;
    *(volatile u16 *)0x10000014 = 0;
    FUN_FFFF0198(0x200);
    if (!IsNotSet()) {
        return 0;
    }
    if (DAT_FFF000E8.unk24 == 0) {
        FUN_FFFF9720(1);
        if (DAT_FFF000E8.unk20 == 0) {
            // kept in a register across the calls below
            Unk_FFF00628 *p = &DAT_FFF00628;
            FUN_FFFF9B08();
            FUN_FFFF47D0();
            FUN_FFFF03A4(0, (void *)0x080F8000, 0x1000);
            FUN_FFFF0868(0x080F8000, 0x1000);
            FUN_FFFF32A8(0, 0x080F8000, 0x1000);
            FUN_FFFF47D0();
            p->unk00 = FUN_FFFFA670();
            p->unk18 = 0;
        }
        FUN_FFFF9AB0(0);
    }
    DAT_FFF000E8.unk24 = 1;
    if (!IsNotSet()) {
        return 0;
    }
    return 1;
}
