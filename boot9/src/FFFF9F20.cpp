#include "types.h"

extern "C" void FUN_FFFF9E98(u16 *reg);
extern "C" void FUN_FFFF9F08();

void FUN_FFFF9F20(u16 *reg)
{
    FUN_FFFF9E98(reg);
    FUN_FFFF9F08();
}
