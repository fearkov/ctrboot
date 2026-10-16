#include "types.h"

typedef void (*Unk_Callback)(void *);

extern "C" u32 FUN_FFFF1F38(void);
extern "C" void FUN_FFFF16B4(s32 index, Unk_Callback cb, void *arg);
extern "C" u8 FUN_FFFF1210(s32 index, u8 value);
extern "C" void FUN_FFFF1390(s32 index, u32 a, u32 b, u32 n, u32 c);
extern "C" void FUN_FFFF2128(u32 x);

void FUN_FFFF1340(s32 index, u32 a, u32 b, u32 n, Unk_Callback cb, void *arg, u32 c)
{
    u8 flag = 0;
    if (n == 0) {
        if (cb != 0) {
            cb(arg);
        }
        return;
    }
    u32 old = FUN_FFFF1F38();
    if (cb != 0) {
        FUN_FFFF16B4(index, cb, arg);
        flag = 1;
    }
    FUN_FFFF1210(index, flag);
    FUN_FFFF1390(index, a, b, n, c);
    FUN_FFFF2128(old);
}
