#include "types.h"

extern "C" volatile u16 *FUN_FFFF4FD4(u32 unit, u32 offset);
extern "C" bool FUN_FFFF4B00(u32 unit);
extern "C" bool FUN_FFFF4B72(u32 unit);
extern "C" bool FUN_FFFF4AE8(u32 unit);
extern "C" bool FUN_FFFF4B5A(u32 unit);

// Whether a controller block has an interrupt pending that is not masked, checked twice.
bool FUN_FFFF4B9C(u32 unit)
{
    u32 pending = 0;

    for (int i = 0; i < 2; i++)
    {
        pending |= *FUN_FFFF4FD4(unit, 0x1C) & ~(*FUN_FFFF4FD4(unit, 0x20) | 0xFCE2);
        pending |= *FUN_FFFF4FD4(unit, 0x1E) & ~(*FUN_FFFF4FD4(unit, 0x22) | 0x7C80);
        pending |= *FUN_FFFF4FD4(unit, 0x36) & ~(*FUN_FFFF4FD4(unit, 0x38) | 0x3FF8);
        pending |= *FUN_FFFF4FD4(unit, 0xF8) & ~(*FUN_FFFF4FD4(unit, 0xFC) | 0xFF24);
        pending |= *FUN_FFFF4FD4(unit, 0xFA) & ~(*FUN_FFFF4FD4(unit, 0xFE) | 0xFF24);
        if (FUN_FFFF4B00(unit) && FUN_FFFF4B72(unit))
        {
            pending |= 1;
        }
        if (FUN_FFFF4AE8(unit) && FUN_FFFF4B5A(unit))
        {
            pending |= 1;
        }
    }
    return pending != 0;
}
