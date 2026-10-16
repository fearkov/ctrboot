#include "types.h"

extern "C" s32 FUN_00012320(u32 id);
extern "C" u32 FUN_00012564();
extern "C" u32 FUN_00011E54(u32 id, s32 count, u8* buffer);
extern "C" void FUN_00011F74(u32 id, u8* buffer, u32 value);
extern "C" void FUN_0001282C(u32 state);
extern u8 DAT_1FFE8520[];

void FUN_00011F28(u32 id, s32 count)
{
    u8* buffer = DAT_1FFE8520 + (id << 8);
    if (count == -1)
        return;
    while (FUN_00012320(id) != 0) {
    }
    u32 state = FUN_00012564();
    u32 value = FUN_00011E54(id, count, buffer);
    FUN_00011F74(id, buffer, value);
    FUN_0001282C(state);
    while (FUN_00012320(id) != 0) {
    }
}
