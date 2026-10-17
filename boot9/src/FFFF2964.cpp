#include "types.h"

extern "C" u32 FUN_FFFF2184(u32 bit);
extern "C" void FUN_FFFF57F4();

// The handler of interrupt 0x10 (FUN_FFFF56C8 installs it): sets the interrupt's bit in the flag word, then does the
// work.
void FUN_FFFF2964()
{
    FUN_FFFF2184(0x10);
    FUN_FFFF57F4();
}
