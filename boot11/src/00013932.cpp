#include "types.h"

extern "C" u32 FUN_000138B8(u32 dev, u8 reg, const u8* data, u32 count);

// Writes count bytes from data to register reg of I2C device 3 (the MCU); returns 1 when the write succeeded.
u32 FUN_00013932(u8 reg, const u8* data, u32 count)
{
    return FUN_000138B8(3, reg, data, count);
}
