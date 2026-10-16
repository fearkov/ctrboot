#include "types.h"

extern "C" void FUN_FFFF0868(u32 start, s32 size);
extern "C" void FUN_FFFFA0A0(u32 a, u32 b, u32 c);
extern "C" void FUN_FFFF9E8C(u32 dst, u32 size, void (*callback)(u32), u32 callbackArg);
extern "C" void FUN_FFFF8A00(u32 mode, u32 a, u32 b, u32 blkcnt, u32 blklen, u32 c, u32 d);
extern "C" void FUN_FFFFAF70(u32 out, u32 src, u32 len, void (*callback)(u32));
extern "C" void FUN_FFFFAE64();

// FUN_FFFFA1C8 with the other key (FUN_FFFFA0A0) and the source read by FUN_FFFFAF70 from src + 0x7E00.
u32 FUN_FFFFA21A(u32 dst, u32 src, u32 size)
{
    FUN_FFFF0868(dst, size);
    FUN_FFFFA0A0(dst, src, size);
    FUN_FFFF9E8C(dst, size, 0, 0);
    FUN_FFFF8A00(4, 5, 5, 0, size >> 4, 0, 0);
    FUN_FFFFAF70(dst, src + 0x7E00, size, 0);
    FUN_FFFFAE64();
    return 1;
}
