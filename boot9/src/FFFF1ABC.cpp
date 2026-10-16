#include "types.h"

extern "C" void FUN_FFFF1AF0();
extern "C" void FUN_FFFF1C68(u32 mode, u32 value);
extern "C" void FUN_FFFF1D80();

extern u32 DAT_FFF00188;
extern volatile u32 DAT_10002000;

void FUN_FFFF1ABC()
{
    if (DAT_FFF00188 == 0) {
        FUN_FFFF1D80();
        FUN_FFFF1C68(0x80000000, 0x60000);
        FUN_FFFF1AF0();
        DAT_10002000 |= 1;
        DAT_FFF00188 = 1;
    }
}
