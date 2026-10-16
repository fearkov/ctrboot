#include "types.h"

extern "C" void FUN_FFFF4E00(u32 unit, u16 low, u16 high);
extern "C" void FUN_FFFF38C0(u32 command, u32 flag);
extern u32 DAT_FFF000B8;

// CMD6 (SWITCH_FUNC, reads the 64-byte status) with the argument for this mode.
void FUN_FFFF5528(u32 mode)
{
    switch (mode)
    {
    case 2:
        FUN_FFFF4E00(DAT_FFF000B8, 1, 0);
        break;
    case 3:
        FUN_FFFF4E00(DAT_FFF000B8, 1, 0x8000);
        break;
    case 0:
        FUN_FFFF4E00(DAT_FFF000B8, 0, 0);
        break;
    default:
        FUN_FFFF4E00(DAT_FFF000B8, 0xFFFF, 0xFF);
        break;
    }
    FUN_FFFF38C0(0x1C06, 1);
}
