#include "types.h"

struct Unk_17E00600 {
    u32 unk0;
    u32 unk4;
    u32 unk8;
    u32 unkC;
    u32 unk10;
    u32 unk14;
    u8 unk18[8];
};

extern "C" u32 FUN_00012564();
extern "C" void FUN_0001282C(u32 state);
extern volatile Unk_17E00600 DAT_17E00600[];

void FUN_0001256C()
{
    u32 state = FUN_00012564();
    DAT_17E00600[1].unk14 = 0x12345678;
    DAT_17E00600[1].unk14 = 0x87654321;
    FUN_0001282C(state);
}
