// The dump keeps the loop end pointer in ip, where armcc picks r3: it goes through a global register variable on
// r12. Four __schedule_barrier() keep the dump's order (the scheduler moves the subs, tst and bics ahead of the
// store or orr before them). The one behind "goto done; done:" gives the return after the last byte store a block
// of its own, so that armcc's conditional execution leaves the store unconditional after "bxeq lr", as in the
// dump, instead of making it strbne.
#pragma arm
#include "types.h"

register u32 gEnd __asm("r12");

// Fills size bytes at dst with the low byte of value: a byte and a halfword to align dst, then words, then the
// remaining halfword and byte.
void FUN_FFFF056C(u8 *dst, u32 value, u32 size)
{
    if (size == 0) {
        return;
    }
    if ((u32)dst & 1) {
        *dst++ = value;
        __schedule_barrier();
        if (--size == 0) {
            return;
        }
    }
    if (size >= 2) {
        value |= value << 8;
        __schedule_barrier();
        if ((u32)dst & 2) {
            *(u16 *)dst = value;
            dst += 2;
            __schedule_barrier();
            if ((size -= 2) == 0) {
                return;
            }
        }
        value |= value << 16;
        __schedule_barrier();
        u32 n = size & ~3u;
        if (n != 0) {
            size -= n;
            gEnd = n + (u32)dst;
            do {
                *(u32 *)dst = value;
                dst += 4;
            } while ((u32)dst < gEnd);
        }
        if (size & 2) {
            *(u16 *)dst = value;
            dst += 2;
        }
    }
    if (!(size & 1)) {
        return;
    }
    *dst = value;
    goto done;
done:
    __schedule_barrier();
}
