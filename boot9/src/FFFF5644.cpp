#include "types.h"

extern "C" u32 FUN_FFFF06EC();
extern "C" u32 FUN_FFFF0700(u32 state);
extern "C" u32 FUN_FFFF1F10(u32 bit);
extern "C" u32 FUN_FFFF1ED4(u32 bit);

// Disables interrupt 0x10 and clears its pending flag, with IRQs masked meanwhile.
void FUN_FFFF5644()
{
    u32 state = FUN_FFFF06EC();
    FUN_FFFF1F10(0x10);
    FUN_FFFF1ED4(0x10);
    FUN_FFFF0700(state);
}
