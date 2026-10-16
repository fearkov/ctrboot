#include "types.h"

extern "C" volatile u16 *FUN_FFFF4FD4(u32 unit, u32 offset);

// Copies the card's response out of the response registers (0x0C..0x1A of a controller block), low byte first:
// mode 0 is a short response (4 bytes), mode 1 a long one (15 bytes, the CRC byte is not kept).
void FUN_FFFF49D8(u32 unit, u32 mode, u8 *out)
{
    u16 value;

    switch (mode)
    {
    case 0:
        value = *FUN_FFFF4FD4(unit, 0x0C);
        out[0] = value;
        out[1] = value >> 8;
        value = *FUN_FFFF4FD4(unit, 0x0E);
        out[2] = value;
        out[3] = value >> 8;
        break;
    case 1:
        value = *FUN_FFFF4FD4(unit, 0x0C);
        out[0] = value;
        out[1] = value >> 8;
        value = *FUN_FFFF4FD4(unit, 0x0E);
        out[2] = value;
        out[3] = value >> 8;
        value = *FUN_FFFF4FD4(unit, 0x10);
        out[4] = value;
        out[5] = value >> 8;
        value = *FUN_FFFF4FD4(unit, 0x12);
        out[6] = value;
        out[7] = value >> 8;
        value = *FUN_FFFF4FD4(unit, 0x14);
        out[8] = value;
        out[9] = value >> 8;
        value = *FUN_FFFF4FD4(unit, 0x16);
        out[10] = value;
        out[11] = value >> 8;
        value = *FUN_FFFF4FD4(unit, 0x18);
        out[12] = value;
        out[13] = value >> 8;
        value = *FUN_FFFF4FD4(unit, 0x1A);
        out[14] = value;
        break;
    }
}
