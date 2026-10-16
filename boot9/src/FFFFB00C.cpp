// Built for space like the other loops of this ROM: the loop test sits at the bottom and is entered by a branch.
#include "types.h"

extern "C" void FUN_FFFF3600(u32 address, u32 size, u8 *dst);
extern "C" u32 FUN_FFFF8930();
extern "C" void FUN_FFFF0428(const void *src, volatile void *dst, u32 size);

// Reads len bytes starting at the flash address src, 0x40 at a time, and writes each piece to the
// AES input FIFO once the FIFO has drained; with a callback, calls it with dst after each piece and
// advances dst by the piece's size.
void FUN_FFFFB00C(u32 out, u32 src, u32 len, void (*callback)(u32))
{
    u8 buf[0x40];
    // a local of its own for the output pointer gives the dump's order of the argument copies at entry
    u32 dst = out;
    while (len != 0) {
        u32 chunk = len & 0x3F;
        if (len >= 0x40) {
            chunk = 0x40;
        }
        FUN_FFFF3600(src, chunk, buf);
        while (FUN_FFFF8930() != 0) {
        }
        FUN_FFFF0428(buf, (volatile void *)0x10009008, chunk);
        if (callback != 0) {
            callback(dst);
            dst += chunk;
        }
        src += chunk;
        len -= chunk;
    }
}
