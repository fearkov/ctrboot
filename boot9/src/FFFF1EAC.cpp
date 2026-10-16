#include "types.h"

extern "C" u32 FUN_FFFF06EC();
extern "C" u32 FUN_FFFF0700(u32 state);

extern u32 DAT_0800003C;

u32 FUN_FFFF1EAC(u32 bit)
{
    u32 state = FUN_FFFF06EC();
    u32 old = (DAT_0800003C >> bit) & 1;
    DAT_0800003C &= ~(1u << bit);
    FUN_FFFF0700(state);
    return old;
}
