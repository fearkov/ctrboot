#include "types.h"

extern u32 DAT_FFF000B8;

extern "C" void FUN_FFFF4E00(u32 unit, u16 low, u16 high);
extern "C" void FUN_FFFF3844(u32 command, u32 checkStatus);

// Command 13 (SEND_STATUS) to the card with this address.
void FUN_FFFF5440(u16 rca)
{
    FUN_FFFF4E00(DAT_FFF000B8, 0, rca);
    FUN_FFFF3844(0xD, 1);
}
