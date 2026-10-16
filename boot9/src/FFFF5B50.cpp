#include "types.h"

extern "C" u32 FUN_FFFF06EC();
extern "C" void FUN_FFFF0700(u32 state);
extern "C" void FUN_FFFF4820(u32 bank, u16 value);
extern "C" void FUN_FFFF4828(u32 bank, u16 value);
extern "C" void FUN_FFFF4818(u32 bank, u16 value);
extern "C" void FUN_FFFF4806(u32 unit);
extern "C" void FUN_FFFF4934(u32 unit, u32 mask);
extern "C" void FUN_FFFF4952(u32 unit, u32 mask);
extern "C" bool FUN_FFFF4C8C(u32 unit);
extern "C" void FUN_FFFF492C(u32 bank, u16 bits);
extern u32 DAT_FFF000B8;

void FUN_FFFF5B50(u32 flag)
{
    u32 state = FUN_FFFF06EC();
    s32 mask = 0x807F;
    FUN_FFFF4820(DAT_FFF000B8, mask);
    FUN_FFFF4828(DAT_FFF000B8, 4);
    FUN_FFFF4818(DAT_FFF000B8, 0x300);
    FUN_FFFF4806(DAT_FFF000B8);
    FUN_FFFF4934(DAT_FFF000B8, mask);
    FUN_FFFF4952(DAT_FFF000B8, 4);
    if (!FUN_FFFF4C8C(DAT_FFF000B8)) {
        u16 bits;
        if (flag) {
            bits = mask >> 7;
        } else {
            bits = 0x200;
        }
        FUN_FFFF492C(DAT_FFF000B8, bits);
    }
    FUN_FFFF0700(state);
}
