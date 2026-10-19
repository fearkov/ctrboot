#include "types.h"

extern "C" void FUN_00012414(u32 value);
extern "C" void FUN_000123B4();
extern "C" void FUN_00011F28(u32 id, s32 count);
extern "C" u32 FUN_00012320(u32 id);
extern u32 DAT_1FFE8114;

void FUN_00012370()
{
    if (DAT_1FFE8114 != 0)
        return;
    s32 i;
    for (i = 0; i < 8; i++)
        FUN_00012414(i);
    FUN_000123B4();
    s32 k = 0;
    for (; i < 15; i++) {
        FUN_00011F28(0, k);
        while (FUN_00012320(0) != 0) {
        }
    }
    DAT_1FFE8114 = 1;
}
