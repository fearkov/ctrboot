#include "types.h"

struct Unk_FFF000C0
{
    u8 pad00[0x34];
    u32 unk34;
    u32 unk38;
};

extern "C" void FUN_FFFF4E00(u32 unit, u16 low, u16 high);
extern "C" void FUN_FFFF3844(u32 command, u32 flag);
extern "C" void FUN_FFFF5CAC(u32 bits);
extern u32 DAT_FFF000B8;
extern Unk_FFF000C0 *DAT_FFF000C0;

void FUN_FFFF51CC(u16 arg)
{
    FUN_FFFF4E00(DAT_FFF000B8, 0, arg);
    FUN_FFFF3844(0x37, 1);
    if (DAT_FFF000C0->unk34 == 0 && (DAT_FFF000C0->unk38 & 0x20) == 0)
    {
        FUN_FFFF5CAC(0x80);
    }
}
