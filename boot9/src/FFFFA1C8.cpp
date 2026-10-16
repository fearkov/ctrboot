#include "types.h"

extern "C" void FUN_FFFF0868(u32 start, s32 size);
extern "C" void FUN_FFFFA050(u32 a, u32 b, u32 c);
extern "C" void FUN_FFFF9E8C(u32 dst, u32 size, void (*callback)(u32), u32 callbackArg);
extern "C" void FUN_FFFF8A00(u32 mode, u32 a, u32 b, u32 blkcnt, u32 blklen, u32 c, u32 d);
extern "C" void FUN_FFFFB00C(u32 out, u32 src, u32 len, void (*callback)(u32));
extern "C" void FUN_FFFFAE64();

// Streams size bytes from src + 0x400 into the AES, whose output goes to dst: invalidates dst in the data cache,
// sets the key and the IV from the arguments (FUN_FFFFA050), starts the output transfer, programs the AES for
// size / 16 blocks and feeds it from FUN_FFFFB00C. Always returns 1. FUN_FFFFA21A and FUN_FFFFA288 are variants.
u32 FUN_FFFFA1C8(u32 dst, u32 src, u32 size)
{
    FUN_FFFF0868(dst, size);
    FUN_FFFFA050(dst, src, size);
    FUN_FFFF9E8C(dst, size, 0, 0);
    FUN_FFFF8A00(4, 5, 5, 0, size >> 4, 0, 0);
    FUN_FFFFB00C(dst, src + 0x400, size, 0);
    FUN_FFFFAE64();
    return 1;
}
