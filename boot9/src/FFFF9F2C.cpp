#include "types.h"

extern "C" void FUN_FFFF9EC0(u16 *reg);
extern "C" void FUN_FFFF9F08();

void FUN_FFFF9F2C(u16 *reg)
{
    FUN_FFFF9EC0(reg);
    FUN_FFFF9F08();
}
