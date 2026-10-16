#include "types.h"

extern "C" void FUN_FFFF5CAC(u32 bits);

void FUN_FFFF2F94(u32 flags)
{
    if (flags & 0x8000) FUN_FFFF5CAC(0x40);
    if (flags & 0x40) FUN_FFFF5CAC(8);
    if (flags & 0x20) FUN_FFFF5CAC(0x20);
    if (flags & 0x10) FUN_FFFF5CAC(0x10);
    if (flags & 0x8) FUN_FFFF5CAC(8);
    if (flags & 0x4) FUN_FFFF5CAC(4);
    if (flags & 0x2) FUN_FFFF5CAC(2);
    if (flags & 0x1) FUN_FFFF5CAC(1);
}
