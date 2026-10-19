#include "types.h"

extern u32 DAT_FFF000C4;
extern volatile u16 DAT_10160000;

// Writes the SPI control register: enabled, device 1, the clock setting kept at 0xFFF000C4 and the chip select held
// while hold is 1. The setting is read through a pointer and combined with hold before the constant: armcc then keeps
// the value in r1 and the shifted hold in r2 as the ROM does.
void FUN_FFFF3698(u32 hold)
{
    u32 *setting = &DAT_FFF000C4;
    u32 value = *setting | (hold << 11);
    DAT_10160000 = value | 0x8100;
}
