#include "types.h"

extern volatile u16 DAT_10146000;

// Reads the key state (active low) as a bit mask and drops the opposite direction of a pair that is held
// together: 0x10 when 0x20 is set, 0x80 when 0x40 is set.
u32 FUN_FFFF4F94()
{
    u32 keys = ~DAT_10146000 & 0xfff;
    return keys & ~((keys & 0x40) << 1) & ~((keys & 0x20) >> 1);
}
