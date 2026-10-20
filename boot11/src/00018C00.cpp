#include "types.h"

extern volatile u32 DAT_10202240;
extern volatile u32 DAT_10202A40;
extern "C" void FUN_00019060(u32 flags);

// Writes value to 0x10202240 when bit 0 of flags is set and to 0x10202A40 when bit 1 is, then rebuilds the
// tables of those screens through FUN_00019060.
void FUN_00018C00(u32 flags, u32 value)
{
    if (flags & 1)
        DAT_10202240 = value;
    if (flags & 2)
        DAT_10202A40 = value;
    FUN_00019060(flags);
}
