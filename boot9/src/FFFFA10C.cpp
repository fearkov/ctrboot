#include "types.h"

extern "C" void FUN_FFFF0868(u32 start, s32 size);
extern "C" void FUN_FFFFA050(u32 dst, u32 src, u32 size);
extern "C" void FUN_FFFF8A00(u32 mode, u32 a, u32 b, u32 blkcnt, u32 blklen, u32 c, u32 d);
extern "C" void FUN_FFFF9F2C(u16 *reg);
extern "C" void FUN_FFFFB00C(u32 dst, u32 src, u32 size, void (*callback)(u32));
extern "C" void FUN_FFFFB05C(u32 dst);
extern "C" void FUN_FFFFAC8C();

// A copy callback for the table at DAT_FFF000C8 (called as copy(dst, src, size), see FUN_FFFFA408): sets up the
// engines (FUN_FFFFA050, FUN_FFFF8A00, FUN_FFFF9F2C) for size / 16 blocks, then FUN_FFFFB00C runs the size bytes at
// src + 0x400 through them into dst, handing each 0x40-byte piece to FUN_FFFFB05C; FUN_FFFFAC8C finishes. Returns 1.
u32 FUN_FFFFA10C(u32 dst, u32 src, u32 size)
{
    FUN_FFFF0868(dst, size);
    FUN_FFFFA050(dst, src, size);
    FUN_FFFF8A00(4, 5, 5, 0, size >> 4, 0, 0);
    // The scratch buffer of FUN_FFFF9F2C is in a block of its own, after the FUN_FFFF8A00 call: that puts it over the
    // stack arguments of that call, as in the dump. Declared at the top of the function it gets a frame of its own
    // above them (0x18 bytes instead of 0xC).
    {
        u16 state[6];
        FUN_FFFF9F2C(state);
    }
    FUN_FFFFB00C(dst, src + 0x400, size, FUN_FFFFB05C);
    FUN_FFFFAC8C();
    return 1;
}
