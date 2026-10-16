#include "types.h"

extern "C" void FUN_FFFF9E10(u32 a, u32 b, u32 c, u32 d);
extern "C" void FUN_FFFF9F08();

void FUN_FFFF9E8C(u32 a, u32 b, u32 c, u32 d)
{
    FUN_FFFF9E10(a, b, c, d);
    FUN_FFFF9F08();
}
