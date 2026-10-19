// Saves the enabled state of all 128 interrupts into the 16 bytes at saved and disables them all, with interrupts off.
// The four stores are one chained assignment: that is what gives armcc the registers the dump has for the address
// and the value (written one by one it swaps them).
#include "types.h"

extern volatile u32 DAT_17E01100[];

extern "C" u32 FUN_00011AC4();
extern "C" u32 FUN_00011AD8(u32 mask);
extern "C" void *FUN_00013254(void *dst, const void *src, u32 size);

void FUN_00012528(u32 *saved)
{
    u32 copy[4];
    u32 state = FUN_00011AC4();
    FUN_00013254(copy, (const void *)DAT_17E01100, 16);
    DAT_17E01100[0x23] = DAT_17E01100[0x22] = DAT_17E01100[0x21] = DAT_17E01100[0x20] = 0xFFFFFFFF;
    FUN_00011AD8(state);
    FUN_00013254(saved, copy, 16);
}
