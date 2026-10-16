#include "types.h"

extern "C" void FUN_FFFF4E00(u32 unit, u16 low, u16 high);
extern "C" void FUN_FFFF38C0(u32 command, u32 flag);
extern u32 DAT_FFF000B8;

void FUN_FFFF536C()
{
    FUN_FFFF4E00(DAT_FFF000B8, 0, 0);
    FUN_FFFF38C0(0x1c08, 1);
}
