#include "types.h"

extern "C" void FUN_FFFF0868(u32 start, s32 size);
extern "C" void FUN_FFFFA050(u32 a, u32 b, u32 c);
extern "C" void FUN_FFFFA030(u32 dst, u32 size, void (*callback)(u32), u32 callbackArg);
extern "C" void FUN_FFFF8A00(u32 mode, u32 a, u32 b, u32 blkcnt, u32 blklen, u32 c, u32 d);
extern "C" u64 FUN_FFFF1F70();
extern "C" u32 FUN_FFFFAD78();
extern "C" void FUN_FFFF9F38();
extern "C" void FUN_FFFF89E4();
extern "C" void FUN_FFFFB00C(u32 out, u32 src, u32 len, void (*callback)(u32));
extern "C" void FUN_FFFFAEB4();

// FUN_FFFFA1C8 with the output transfer set up by FUN_FFFFA030 and a wait before the AES is fed: until FUN_FFFFAD78
// returns non-zero, for at most 0x417 ticks of the 64-bit counter FUN_FFFF1F70. On a timeout it stops
// (FUN_FFFF9F38, FUN_FFFF89E4) and returns 0.
u32 FUN_FFFFA288(u32 dst, u32 src, u32 size)
{
    u32 result = 1;
    FUN_FFFF0868(dst, size);
    FUN_FFFFA050(dst, src, size);
    FUN_FFFFA030(dst, size, 0, 0);
    FUN_FFFF8A00(4, 5, 5, 0, size >> 4, 0, 0);
    u64 start = FUN_FFFF1F70();
    while (FUN_FFFFAD78() == 0) {
        if (FUN_FFFF1F70() - start > 0x417) {
            FUN_FFFF9F38();
            FUN_FFFF89E4();
            result = 0;
            break;
        }
    }
    if (result != 0) {
        FUN_FFFFB00C(dst, src + 0x400, size, 0);
        FUN_FFFFAEB4();
    }
    return result;
}
