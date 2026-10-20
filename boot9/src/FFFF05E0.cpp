// Built with the optimizer's O2 (#pragma O2): at -O3 armcc splits the post-indexed copies through a spare
// register and saves r4 for it. The dump keeps the dummy read, the pointer xor, the halfwords of the shifted
// copy and the loop end pointers in ip, where armcc picks r3: they go through a global register variable on
// r12. Five __schedule_barrier() keep the dump's order (the scheduler moves the subs and the lsr ahead of
// the stores). The two behind "goto oddDone; oddDone:" and "goto done; done:" give the return after each
// last byte store a block of its own, so that armcc's conditional execution leaves the store unconditional
// after "bxeq lr", as in the dump, instead of making it strbne. "(size -= 2) < (u32)-2" is the borrow of
// "subs r2, r2, #2", and the gotos give the shifted copy loop its test at the top and at the bottom.
#pragma arm
#pragma O2
#include "types.h"

register u32 gScratch __asm("r12");

// Copies size bytes from src to dst, a byte, halfword or word at a time as their alignment allows.
void FUN_FFFF05E0(const u8 *src, u8 *dst, u32 size)
{
    if (size == 0) {
        return;
    }
    if ((u32)dst & 1) {
        gScratch = *(volatile u8 *)dst;
        *dst++ = *src++;
        __schedule_barrier();
        if (--size == 0) {
            return;
        }
    }
    gScratch = (u32)dst ^ (u32)src;
    if (gScratch & 1) {
        // Source and destination differ in bit 0: halfword reads shifted by a byte into halfword writes.
        const u16 *s = (const u16 *)((u32)src & ~1u);
        u16 *d = (u16 *)dst;
        gScratch = *s++;
        u32 carry = gScratch >> 8;
        __schedule_barrier();
        if ((size -= 2) >= (u32)-2) {
            goto odd;
        }
    loop:
        gScratch = *s++;
        gScratch = carry | (gScratch << 8);
        *d++ = gScratch;
        __schedule_barrier();
        carry = gScratch >> 16;
        __schedule_barrier();
        if ((size -= 2) < (u32)-2) {
            goto loop;
        }
    odd:
        if (!(size & 1)) {
            return;
        }
        *(u8 *)d = carry;
        goto oddDone;
    oddDone:
        __schedule_barrier();
        return;
    }
    if (gScratch & 2) {
        u32 n = size & ~1u;
        if (n != 0) {
            size -= n;
            gScratch = n + (u32)dst;
            do {
                *(u16 *)dst = *(const u16 *)src;
                dst += 2;
                src += 2;
            } while ((u32)dst < gScratch);
        }
    } else if (size >= 2) {
        if ((u32)dst & 2) {
            *(u16 *)dst = *(const u16 *)src;
            dst += 2;
            src += 2;
            __schedule_barrier();
            if ((size -= 2) == 0) {
                return;
            }
        }
        u32 n = size & ~3u;
        if (n != 0) {
            size -= n;
            gScratch = n + (u32)dst;
            do {
                *(u32 *)dst = *(const u32 *)src;
                dst += 4;
                src += 4;
            } while ((u32)dst < gScratch);
        }
        if (size & 2) {
            *(u16 *)dst = *(const u16 *)src;
            dst += 2;
            src += 2;
        }
    }
    if (!(size & 1)) {
        return;
    }
    *dst = *src;
    goto done;
done:
    __schedule_barrier();
}
