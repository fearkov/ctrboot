#include "types.h"

extern "C" u32 FUN_FFFFAD58();
extern "C" void FUN_FFFFACDC(u16 *reg);
extern "C" void FUN_FFFFADE0(u16 *reg);

void FUN_FFFF9EC0(u16 *reg)
{
    while (FUN_FFFFAD58()) {
    }
    FUN_FFFFACDC(reg);
    *reg &= ~0x404;
    *reg |= 0x100;
    FUN_FFFFADE0(reg);
}
