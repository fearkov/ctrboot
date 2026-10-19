#include "types.h"

typedef void (*PutCharFunc)(u32 screen, u32 x, u32 y, u32 color, u32 ch);

extern "C" void FUN_000189A0(u32 screen, u32 x, u32 y, u32 color, const char *str, PutCharFunc putChar, u32 margin, u32 lineGap);
extern u32 DAT_1FFE80C4;

void FUN_00018950(u32 x, u32 y, u32 color, const char *str, PutCharFunc putChar, u32 margin, u32 lineGap)
{
    if (DAT_1FFE80C4 & 1)
        FUN_000189A0(0, x, y, color, str, putChar, margin, lineGap);
    if (DAT_1FFE80C4 & 2)
        FUN_000189A0(1, x, y, color, str, putChar, margin, lineGap);
}
