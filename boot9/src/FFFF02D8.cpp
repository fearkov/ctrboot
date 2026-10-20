// The count lives in ip and the data in r3. armcc gives r3 to a local count (and ip to the data), so the
// count is a global register variable on r12.
#pragma arm
#include "types.h"

register s32 gCount __asm("r12");

// Copies size bytes from a single word port at src to a single word port at dst, a word at a time.
void FUN_FFFF02D8(const volatile u32 *src, volatile u32 *dst, s32 size)
{
    for (gCount = 0; gCount < size; gCount += 4) {
        *dst = *src;
    }
}
