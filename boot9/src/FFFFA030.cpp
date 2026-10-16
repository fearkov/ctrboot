#include "types.h"

extern "C" void FUN_FFFF9F64(u32 b);
extern "C" void FUN_FFFF9FB0(u32 a, u32 b, u32 c, u32 d);

void FUN_FFFFA030(u32 a, u32 b, u32 c, u32 d)
{
    FUN_FFFF9F64(b);
    FUN_FFFF9FB0(a, b, c, d);
}
