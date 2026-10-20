// The offset lives in ip and the data in r3. armcc gives r3 to a local offset (and ip to the data), so the
// offset is a global register variable on r12.
#pragma arm
#include "types.h"

register s32 gOffset __asm("r12");

// Copies size bytes from src to dst, a halfword at a time.
void FUN_FFFF030C(const u8 *src, u8 *dst, s32 size)
{
    for (gOffset = 0; gOffset < size; gOffset += 2) {
        *(u16 *)(dst + gOffset) = *(const u16 *)(src + gOffset);
    }
}
