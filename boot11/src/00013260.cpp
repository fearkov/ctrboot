#pragma arm
#include "types.h"

// Little-endian 32-bit read from a possibly unaligned address, one byte at a time.
u32 FUN_00013260(const u8 *p)
{
    u32 b0 = p[0];
    u32 b1 = p[1];
    u32 b2 = p[2];
    u32 b3 = p[3];
    return b0 | (b1 << 8) | (b2 << 16) | (b3 << 24);
}
