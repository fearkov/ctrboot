// FUN_000127C8 keeps a value in r3 across its calls of FUN_000128E4, so that one is defined first in this file:
// armcc then knows it leaves r3 alone.
#include "types.h"

// The MPCore private timer and watchdog, 0x20 bytes apart.
struct Unk_17E00600 {
    u32 unk0;
    u32 unk4;
    u32 unk8;
    u32 unkC;
    u32 unk10;
    u32 unk14;
    u8 unk18[8];
};

struct Unk_1FFE80C8 {
    u8 unk0[4];
    u32 unk4;
};

extern "C" u32 FUN_00012564();
extern "C" void FUN_0001256C();
extern "C" void FUN_0001282C(u32 state);
extern volatile Unk_17E00600 DAT_17E00600[];

void FUN_000128E4(s32 index)
{
    DAT_17E00600[index].unk8 = 0;
    DAT_17E00600[index].unkC = 1;
}

void FUN_000127C8()
{
    // The variables are reached by absolute address, not through DAT_ symbols: knowing 0x1FFE80C8, armcc forms the
    // address of the two bytes from it (adds r1, r4, #2) instead of loading another literal.
    Unk_1FFE80C8* vars = (Unk_1FFE80C8*)0x1FFE80C8;
    if (vars->unk4 == 0) {
        u32 state = FUN_00012564();
        vars->unk4 = 1;
        FUN_000128E4(0);
        FUN_000128E4(1);
        DAT_17E00600[1].unk10 = 1;
        FUN_0001256C();
        u8* control = (u8*)0x1FFE80CA;
        control[0] = 0;
        control[1] = 0;
        FUN_0001282C(state);
    }
}
