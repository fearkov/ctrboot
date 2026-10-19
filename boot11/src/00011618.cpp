// The offset lives in ip and the data in r3. armcc gives r3 to a local offset (and ip to the data, and it
// moves the add between the load and the store), so the offset is a global register variable on r12.
#pragma arm
#include "types.h"

register s32 gOffset __asm("r12");

// Copies size bytes, a word at a time, from one fixed address to another (both are ports, so neither
// pointer advances).
void FUN_00011618(volatile u32 *src, volatile u32 *dst, s32 size)
{
    for (gOffset = 0; gOffset < size; gOffset += 4) {
        *dst = *src;
    }
}
