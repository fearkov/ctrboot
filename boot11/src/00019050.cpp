// FUN_00018EBC is in this file, after FUN_00019050: armcc then knows that one is a leaf that needs no aligned stack,
// so FUN_00018EBC pushes only lr.
#include "types.h"

extern u32 DAT_1FFE80C4;

u32 FUN_00019050(u32 value)
{
    u32 old = DAT_1FFE80C4;
    DAT_1FFE80C4 = value;
    return old;
}

void FUN_00018EBC(u32 flags)
{
    FUN_00019050(flags | DAT_1FFE80C4);
}
