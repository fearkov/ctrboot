#include "types.h"

struct Unk_FFF000C0
{
    u8 pad00[0x34];
    u32 unk34;
};

extern "C" void FUN_FFFF4E00(u32 unit, u16 lo, u16 hi);
extern "C" void FUN_FFFF3844(u16 command, u32 flag);
extern "C" bool FUN_FFFF4A86(u32 unit);
extern u32 DAT_FFF000B8;
extern Unk_FFF000C0 *DAT_FFF000C0;

void FUN_FFFF55B4(u32 mode)
{
    if (mode) {
        FUN_FFFF4E00(DAT_FFF000B8, 0x100, 0x3B9);
    } else {
        FUN_FFFF4E00(DAT_FFF000B8, 0, 0x3B9);
    }
    FUN_FFFF3844(0x506, 1);
    while (FUN_FFFF4A86(DAT_FFF000B8)) {
        if (DAT_FFF000C0->unk34 != 0) {
            return;
        }
    }
}
