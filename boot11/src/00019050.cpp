#include "types.h"

extern u32 DAT_1FFE80C4;

u32 FUN_00019050(u32 value)
{
    u32 old = DAT_1FFE80C4;
    DAT_1FFE80C4 = value;
    return old;
}
