// Built for space: only -Ospace gives this code, like its neighbours in this part of boot9.
#pragma Ospace
#include "types.h"

struct Unk_10164000 {
    u8 unk0[4];
    volatile u32 unk4;
};
extern Unk_10164000 DAT_10164000;

extern "C" void FUN_FFFF1D94(u32 n);

void FUN_FFFF35C0(u32 n)
{
    while ((s32)DAT_10164000.unk4 < 0) {}
    if (n <= 7) {
        FUN_FFFF1D94(n);
    }
}
