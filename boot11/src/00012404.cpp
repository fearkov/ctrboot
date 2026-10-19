#include "types.h"

extern volatile u32 DAT_10200D00[];
extern u8 DAT_1FFE8118[];

extern "C" u32 FUN_00012564();
extern "C" void FUN_0001282C(u32 state);

u32 FUN_00012404()
{
    return DAT_10200D00[0] & 1;
}

void FUN_00012414(u32 value)
{
    u8* buf = DAT_1FFE8118;
    u32 state = FUN_00012564();
    while (FUN_00012404() != 0) {
    }
    ((u32*)DAT_1FFE8118)[0] = 0;
    ((u32*)DAT_1FFE8118)[1] = 0;
    buf[0] = 1;
    buf[1] = value;
    buf[2] = 1;
    DAT_10200D00[2] = ((u32*)DAT_1FFE8118)[0];
    DAT_10200D00[3] = ((u32*)DAT_1FFE8118)[1];
    DAT_10200D00[1] = 0;
    FUN_0001282C(state);
}
