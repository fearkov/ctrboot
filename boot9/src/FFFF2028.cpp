// Built for space (armcc's default), like the other one-shot initialisers of this ROM.
#pragma Ospace
#include "types.h"

struct Unk_10001000 {
    u32 unk0;
    u32 unk4;
};

extern u32 DAT_FFF00148;
extern Unk_10001000 DAT_10001000;
extern u8 DAT_FFFF0C78;

extern "C" u32 FUN_FFFF06EC();
extern "C" void FUN_FFFF1764();
extern "C" u32 FUN_FFFF06D8();

void FUN_FFFF2028()
{
    if (DAT_FFF00148 == 0) {
        DAT_FFF00148 = 1;
        FUN_FFFF06EC();
        FUN_FFFF1764();
        ((u32 *)0x08000000)[1] = (u32)&DAT_FFFF0C78;
        DAT_10001000.unk0 = 0;
        DAT_10001000.unk4 = 0xFFFFFFFF;
        FUN_FFFF06D8();
    }
}
