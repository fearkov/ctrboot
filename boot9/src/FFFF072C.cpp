#include "types.h"

#pragma arm

// Masks FIQs; returns the previous F bit (0x40 if they were already masked).
u32 FUN_FFFF072C()
{
    return __disable_fiq();
}
