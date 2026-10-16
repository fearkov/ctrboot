// Built for space like the other loops of this ROM: the loop test sits at the bottom and is entered by a branch.
#include "types.h"

extern "C" void FUN_FFFF46CC(u32 src, u32 *dst, s32 size);
extern "C" u32 FUN_FFFF8930();
extern "C" void FUN_FFFF0428(const void *src, volatile void *dst, u32 size);

// Takes len bytes starting at src, 0x200 at a time (FUN_FFFF46CC fills a stack buffer), and writes the
// buffer to the AES input FIFO in 0x40-byte pieces once the FIFO has drained; with a callback, calls it
// with dst after each piece and advances dst by 0x40.
void FUN_FFFFAF70(u32 out, u32 src, u32 len, void (*callback)(u32))
{
    u32 buf[0x80];
    // a local of its own for the output pointer gives the dump's order of the argument copies at entry
    u32 dst = out;
    while (len != 0) {
        u32 chunk = len & 0x1FF;
        if (len >= 0x200) {
            chunk = 0x200;
        }
        FUN_FFFF46CC(src, buf, chunk);
        for (s32 off = 0; off < chunk; off += 0x40) {
            while (FUN_FFFF8930() != 0) {
            }
            FUN_FFFF0428(&buf[off / 4], (volatile void *)0x10009008, 0x40);
            if (callback != 0) {
                callback(dst);
                dst += 0x40;
            }
        }
        src += chunk;
        len -= chunk;
    }
}
