// Built for space like the rest of the SD/MMC command code: the loop test sits at the bottom and is entered by a branch.
#pragma Ospace
#include "types.h"

struct Unk_FFF000C0
{
    u8 pad00[0x34];
    u32 unk34;
};

extern "C" u32 FUN_FFFF4A86(u32 unit);
extern "C" void FUN_FFFF4E00(u32 unit, u16 low, u16 high);
extern "C" void FUN_FFFF4848(u32 unit, u16 value);
extern u32 DAT_FFF000B8;
extern Unk_FFF000C0 *DAT_FFF000C0;

void FUN_FFFF5240()
{
    while (FUN_FFFF4A86(DAT_FFF000B8) != 0)
    {
        if (DAT_FFF000C0->unk34 != 0)
        {
            return;
        }
    }
    FUN_FFFF4E00(DAT_FFF000B8, 0, 0);
    FUN_FFFF4848(DAT_FFF000B8, 0);
}
