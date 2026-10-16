#include "types.h"

extern u32 DAT_FFF000B8;

extern "C" void FUN_FFFF4E00(u32 unit, u16 low, u16 high);
extern "C" void FUN_FFFF3844(u32 command, u32 checkStatus);

// Application command 6 (SET_BUS_WIDTH): width 0 is one bit (argument 0), width 1 is four bits (argument 2);
// any other width sends nothing. The call is repeated in each case, which is what gets the unit loaded before the
// test and the two calls merged again afterwards.
void FUN_FFFF547C(u32 width)
{
    switch (width) {
    case 0:
        FUN_FFFF4E00(DAT_FFF000B8, 0, 0);
        break;
    case 1:
        FUN_FFFF4E00(DAT_FFF000B8, 2, 0);
        break;
    default:
        return;
    }
    FUN_FFFF3844(0x46, 1);
}
