#include "types.h"

extern "C" void FUN_FFFF48B4(u32 unit);
extern "C" void FUN_FFFF489E(u32 unit);
extern "C" void FUN_FFFF4DB0(u32 unit, u32 mode);
extern "C" void FUN_FFFF4E84(u32 unit, u16 first, u16 second);
extern "C" volatile u16 *FUN_FFFF4FD4(u32 unit, u32 offset);

// The register at offset of controller block unit: 1 selects 0x10006000, anything else 0x10007000.
static inline volatile u16 *Reg(u32 unit, u32 offset)
{
    return (volatile u16 *)((unit == 1 ? 0x10006000 : 0x10007000) + offset);
}

// Brings one of the two controller blocks into its initial state.
void FUN_FFFF4CC4(u32 unit)
{
    FUN_FFFF48B4(unit);
    FUN_FFFF489E(unit);
    FUN_FFFF4DB0(unit, 0);
    FUN_FFFF4DB0(unit, 1);
    FUN_FFFF4E84(unit, 0, 1);

    volatile u16 *reset = Reg(unit, 0xE0);
    *reset &= ~1;
    *reset |= 1;

    *FUN_FFFF4FD4(unit, 0x20) |= 0x31D;
    *FUN_FFFF4FD4(unit, 0x22) |= 0x837F;
    *FUN_FFFF4FD4(unit, 0xFC) |= 0xDB;
    *FUN_FFFF4FD4(unit, 0xFE) |= 0xDB;
    *FUN_FFFF4FD4(unit, 0x24) = 0x20;
    *FUN_FFFF4FD4(unit, 0x28) = 0x40EE;

    *Reg(unit, 2) &= ~3;
}
