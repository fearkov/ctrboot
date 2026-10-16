#include "types.h"

extern u32 DAT_FFF000B8;

extern "C" void FUN_FFFF4E00(u32 unit, u16 low, u16 high);
extern "C" void FUN_FFFF38C0(u32 command, u32 flag);

// Application command 51 (SEND_SCR), the variant of the command sender that sets up a data stage.
void FUN_FFFF5424()
{
    FUN_FFFF4E00(DAT_FFF000B8, 0, 0);
    FUN_FFFF38C0(0x73, 1);
}
