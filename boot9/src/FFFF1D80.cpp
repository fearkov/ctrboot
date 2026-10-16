#include "types.h"

extern "C" void FUN_FFFF1D94(u32 index);

void FUN_FFFF1D80()
{
    for (int i = 0; i <= 7; i++) {
        FUN_FFFF1D94(i);
    }
}
