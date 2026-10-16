#include "types.h"

extern "C" u32 FUN_FFFF1A9C(u32 index);
extern "C" u32 FUN_FFFF1F38(void);
extern "C" u32 FUN_FFFF1086(u32 a, u32 b, u8 *buf);
extern "C" void FUN_FFFF1424(u32 index, u8 *buf, u32 size);
extern "C" void FUN_FFFF2128(u32 x);

void FUN_FFFF13D8(u32 index, s32 arg)
{
    u8 *buf = (u8 *)0x080FD000 + (index << 8);
    if (arg != -1) {
        while (FUN_FFFF1A9C(index) != 0) {
        }
        u32 old = FUN_FFFF1F38();
        u32 size = FUN_FFFF1086(index, arg, buf);
        FUN_FFFF1424(index, buf, size);
        FUN_FFFF2128(old);
        while (FUN_FFFF1A9C(index) != 0) {
        }
    }
}
