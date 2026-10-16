#include "types.h"

extern "C" void FUN_FFFF1AB0();
extern "C" void FUN_FFFFAD18();
extern "C" void FUN_FFFF9F08();

extern u32 DAT_FFF00078;

// One-time setup: DAT_FFF00078 is the done flag.
void FUN_FFFFACF8()
{
    if (DAT_FFF00078 == 0) {
        FUN_FFFF1AB0();
        FUN_FFFFAD18();
        FUN_FFFF9F08();
        DAT_FFF00078 = 1;
    }
}
