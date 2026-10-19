// The offset lives in ip and the data in r3. armcc gives r3 to a local offset (and lr and ip to the data
// and a second copy of the offset, since it moves the add above the store), so the offset is a global
// register variable on r12.
#pragma arm
#include "types.h"

register s32 gOffset __asm("r12");

// Copies size bytes from a single halfword port at src to dst, a halfword at a time.
void FUN_00011684(volatile const u16 *src, u8 *dst, s32 size)
{
    for (gOffset = 0; gOffset < size; gOffset += 2) {
        *(u16 *)(dst + gOffset) = *src;
    }
}
