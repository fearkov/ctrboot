#include "types.h"

struct Unk_FFF000C0 {
    u8 pad00[0x34];
    u32 unk34;
};

extern "C" bool FUN_FFFF4A86(u32 unit);
extern "C" void FUN_FFFF4828(u32 bank, u16 value);
extern "C" void FUN_FFFF4820(u32 bank, u16 value);
extern "C" void FUN_FFFF4934(u32 bank, u32 mask);
extern "C" void FUN_FFFF4848(u32 bank, u16 value);
extern "C" bool FUN_FFFF4C7C(u32 bank, u32 mask);
extern "C" void FUN_FFFF4896(u32 bank, u16 value);
extern "C" void FUN_FFFF510C();
extern u32 DAT_FFF000B8;
extern Unk_FFF000C0 *DAT_FFF000C0;

void FUN_FFFF3844(u16 command, u32 flag)
{
    while (FUN_FFFF4A86(DAT_FFF000B8)) {
        if (DAT_FFF000C0->unk34) {
            return;
        }
    }
    FUN_FFFF4828(DAT_FFF000B8, 1);
    FUN_FFFF4820(DAT_FFF000B8, 0x807F);
    FUN_FFFF4934(DAT_FFF000B8, 0x807F);
    FUN_FFFF4848(DAT_FFF000B8, command);
    while (!FUN_FFFF4C7C(DAT_FFF000B8, 1)) {
        if (DAT_FFF000C0->unk34) {
            break;
        }
    }
    FUN_FFFF4896(DAT_FFF000B8, 0x807F);
    if (flag && !DAT_FFF000C0->unk34) {
        FUN_FFFF510C();
    }
}
