#include "types.h"

extern "C" void FUN_FFFF4E00(u32 unit, u16 low, u16 high);
extern "C" void FUN_FFFF38C0(u32 command, u32 flag);
extern u32 DAT_FFF000B8;

// Sends a command with an address argument: a card that is not block-addressed (block == 0) takes byte
// addresses, so the block address is shifted by 9.
void FUN_FFFF5278(u32 address, u32 block)
{
    if (block == 0)
    {
        address <<= 9;
    }
    FUN_FFFF4E00(DAT_FFF000B8, address, address >> 16);
    FUN_FFFF38C0(0x12, 1);
}
