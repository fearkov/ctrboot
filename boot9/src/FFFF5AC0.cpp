#include "types.h"

extern "C" void FUN_FFFF3CB4(u32 unit);

u32 FUN_FFFF5AC0(u32 unit, u32 a, u32 b)
{
    if (a != 0 || b != 0)
    {
        FUN_FFFF3CB4(unit);
        return 1;
    }
    return 0;
}
