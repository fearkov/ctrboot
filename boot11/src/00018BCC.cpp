#include "types.h"

struct Unk_10202000 {
    u8 pad0[0x14];
    u32 unk14;
};

extern "C" u32 FUN_000121EC();
extern "C" u32 FUN_00012564();
extern "C" void FUN_0001282C(u32 state);
extern "C" void FUN_00018434(u32 bit, u32 value);
extern "C" void FUN_00018450(u32 bit, u32 value);
extern volatile Unk_10202000 DAT_10202000;

void FUN_00018BCC(u32 value)
{
    DAT_10202000.unk14 = value;
    if (FUN_000121EC() == 0) {
        u32 state = FUN_00012564();
        FUN_00018450(10, 1);
        FUN_00018434(10, value);
        FUN_0001282C(state);
    }
}
