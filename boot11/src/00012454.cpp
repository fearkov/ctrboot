#include "types.h"

extern void (*DAT_1FFE8028)(u32);

extern "C" u32 FUN_000120AE();
extern "C" void FUN_00011FFC(u32 value);

void FUN_00012454()
{
    u32 value = FUN_000120AE();
    if (DAT_1FFE8028 != 0)
        DAT_1FFE8028(value);
    FUN_00011FFC(value);
}
