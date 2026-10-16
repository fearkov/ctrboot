#include "types.h"

extern "C" void FUN_FFFF0868(u32 start, s32 size);
extern "C" void FUN_FFFFA0A0(u32 dst, u32 src, u32 size);
extern "C" void FUN_FFFF8A00(u32 mode, u32 a, u32 b, u32 blkcnt, u32 blklen, u32 c, u32 d);
extern "C" void FUN_FFFF9F2C(u16 *reg);
extern "C" void FUN_FFFFAF70(u32 dst, u32 src, u32 size, void (*callback)(u32));
extern "C" void FUN_FFFFAFE0(u32 dst);
extern "C" void FUN_FFFFAC8C();

// A copy callback for the table at DAT_FFF000C8 (called as copy(dst, src, size), see FUN_FFFFA408): the same as
// FUN_FFFFA10C, with the other key setup (FUN_FFFFA0A0), the data at src + 0x7E00 (FUN_FFFFAF70) and the callback
// FUN_FFFFAFE0.
u32 FUN_FFFFA15C(u32 dst, u32 src, u32 size)
{
    FUN_FFFF0868(dst, size);
    FUN_FFFFA0A0(dst, src, size);
    FUN_FFFF8A00(4, 5, 5, 0, size >> 4, 0, 0);
    // in a block of its own, over the stack arguments above: see FUN_FFFFA10C
    {
        u16 state[6];
        FUN_FFFF9F2C(state);
    }
    FUN_FFFFAF70(dst, src + 0x7E00, size, FUN_FFFFAFE0);
    FUN_FFFFAC8C();
    return 1;
}
