#include "types.h"

// Returns the NDMA control bits (address updates, repeat and interrupt) for a transfer mode.
u32 FUN_FFFF1098(u32 mode)
{
    switch (mode) {
    case 0:
        return 0x6000;
    case 2:
    case 8:
        return 0x800;
    case 9:
        return 0x40000800;
    case 3:
        return 0x4000;
    case 4:
        return 0x4800;
    case 10:
        return 0x60005000;
    case 5:
        return 0x20001000;
    case 6:
        return 0x60001000;
    case 7:
        return 0x20000800;
    default:
        return 0;
    }
}
