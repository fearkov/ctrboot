#include "types.h"

extern u32 DAT_FFF000B8;

extern "C" void FUN_FFFF4E00(u32 unit, u16 low, u16 high);
extern "C" void FUN_FFFF3844(u32 command, u32 checkStatus);

// Command 3 as the MMC SET_RELATIVE_ADDR: the card is given this address.
void FUN_FFFF54D0(u16 rca)
{
    FUN_FFFF4E00(DAT_FFF000B8, 0, rca);
    FUN_FFFF3844(0x403, 1);
}
