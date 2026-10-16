#include "types.h"

struct Unk_10163000 {
    u32 unk0;
    u16 unk4;
    u16 unk6;
    u32 unk8;
    u32 unkC;
};

extern volatile Unk_10163000 DAT_10163000;

extern "C" u32 FUN_00012564();
extern "C" void FUN_0001282C(u32 state);

s32 FUN_000122BC(u32* out)
{
    if (DAT_10163000.unk4 & 0x4000) {
        DAT_10163000.unk4 |= 0xC000;
        return -3;
    }
    u32 state = FUN_00012564();
    if (DAT_10163000.unk4 & 0x100) {
        FUN_0001282C(state);
        return -4;
    }
    *out = DAT_10163000.unkC;
    FUN_0001282C(state);
    return 0;
}
