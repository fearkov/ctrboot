#include "types.h"

extern "C" u32 FUN_FFFF06EC();
extern "C" u32 FUN_FFFF0700(u32 state);

// Sets bit `bit` of the flag word at 0x0800003C and returns what it was.
u32 FUN_FFFF2184(u32 bit)
{
    u32 state = FUN_FFFF06EC();
    u32 *flags = (u32 *)0x0800003C;
    u32 was = (*flags >> bit) & 1;
    *flags |= 1u << bit;
    FUN_FFFF0700(state);
    return was;
}
