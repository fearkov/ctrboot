// Built for space: only -Ospace gives this code, like its neighbours in this part of boot9.
#pragma Ospace
#include "types.h"

struct Unk_FFF000C0 {
    u8 pad00[0x34];
    u32 unk34;
};

extern "C" bool FUN_FFFF4A86(u32 unit);
extern "C" void FUN_FFFF4828(u32 bank, u16 value);
extern "C" void FUN_FFFF5B50(u32 flag);
extern "C" void FUN_FFFF4848(u32 bank, u16 value);
extern u32 DAT_FFF000B8;
extern Unk_FFF000C0 *DAT_FFF000C0;

void FUN_FFFF38C0(u16 command, u32 flag)
{
    while (FUN_FFFF4A86(DAT_FFF000B8)) {
        if (DAT_FFF000C0->unk34) {
            return;
        }
    }
    FUN_FFFF4828(DAT_FFF000B8, 1);
    FUN_FFFF5B50(flag);
    FUN_FFFF4848(DAT_FFF000B8, command);
}
