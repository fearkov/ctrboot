#include "types.h"

extern u32 DAT_FFF000B8;

extern "C" void FUN_FFFF4E00(u32 unit, u16 low, u16 high);
extern "C" void FUN_FFFF3844(u32 command, u32 checkStatus);

// Command 8 (SEND_IF_COND) with the voltage range and check pattern 0x1AA as its argument.
void FUN_FFFF538C()
{
    FUN_FFFF4E00(DAT_FFF000B8, 0x1AA, 0);
    FUN_FFFF3844(0x408, 0);
}
