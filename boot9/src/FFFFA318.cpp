#include "types.h"

extern "C" void FUN_FFFF0868(u32 start, s32 size);
extern "C" void FUN_FFFFA0A0(u32 a, u32 b, u32 c);
extern "C" void FUN_FFFFA030(u32 a, u32 b, u32 c, u32 d);
extern "C" void FUN_FFFF8A00(u32 mode, u32 a, u32 b, u32 blkcnt, u32 blklen, u32 c, u32 d);
extern "C" u64 FUN_FFFF1F70();
extern "C" u32 FUN_FFFFAD78();
extern "C" void FUN_FFFF9F38();
extern "C" void FUN_FFFF89E4();
extern "C" void FUN_FFFFAF70(u32 out, u32 src, u32 len, void (*callback)(u32));
extern "C" void FUN_FFFFAEB4();

// Like FUN_FFFFA21A, but it waits for FUN_FFFFAD78 to report done for at most 0x417 ticks of the clock: on a timeout
// it runs the cleanup (FUN_FFFF9F38, FUN_FFFF89E4) and returns 0 without the transfer (FUN_FFFFAF70).
u32 FUN_FFFFA318(u32 dst, u32 src, u32 size)
{
    u32 result = 1;
    FUN_FFFF0868(dst, size);
    FUN_FFFFA0A0(dst, src, size);
    FUN_FFFFA030(dst, size, 0, 0);
    FUN_FFFF8A00(4, 5, 5, 0, size >> 4, 0, 0);
    u64 start = FUN_FFFF1F70();
    while (!FUN_FFFFAD78()) {
        if (FUN_FFFF1F70() - start > 0x417) {
            FUN_FFFF9F38();
            FUN_FFFF89E4();
            result = 0;
            break;
        }
    }
    if (result) {
        FUN_FFFFAF70(dst, src + 0x7E00, size, 0);
        FUN_FFFFAEB4();
    }
    return result;
}
