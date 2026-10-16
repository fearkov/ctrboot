#include "types.h"

extern "C" void FUN_00018F94();
extern "C" u32 FUN_000188E4();
extern "C" u32 FUN_000184CC();

u32 FUN_00018FD8()
{
    FUN_00018F94();
    if (FUN_000188E4() != 0 && FUN_000184CC() != 0)
        return 1;
    return 0;
}
