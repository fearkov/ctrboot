#pragma arm
#include "types.h"

extern "C" u32 FUN_00011E64(s32 enable);

// Switches the GPU's power and clock bits on and returns the previous value of the flag that records it.
u32 FUN_00011E4C()
{
    return FUN_00011E64(1);
}
