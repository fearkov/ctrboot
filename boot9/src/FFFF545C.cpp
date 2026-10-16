#include "types.h"

extern u32 DAT_FFF000B8;

extern "C" void FUN_FFFF4E00(u32 unit, u16 low, u16 high);
extern "C" void FUN_FFFF3844(u32 command, u32 checkStatus);

// Command 16 (SET_BLOCKLEN).
void FUN_FFFF545C(u32 length)
{
    FUN_FFFF4E00(DAT_FFF000B8, length, length >> 16);
    FUN_FFFF3844(0x10, 1);
}
