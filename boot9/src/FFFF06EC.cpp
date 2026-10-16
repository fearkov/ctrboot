#include "types.h"

#pragma arm

// Masks IRQs; returns the previous I bit (0x80 if they were already masked).
u32 FUN_FFFF06EC()
{
    return __disable_irq();
}
