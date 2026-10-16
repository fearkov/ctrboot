#include "types.h"

void FUN_FFFF1DFC(u32 index)
{
    volatile s32 *reg = (volatile s32 *)(0x1000201C + index * 0x1C);
    while (*reg < 0) {
    }
}
