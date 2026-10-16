#include "types.h"

extern u32 DAT_FFF000B8;

extern "C" void FUN_FFFF4E00(u32 unit, u16 low, u16 high);
extern "C" void FUN_FFFF3844(u32 command, u32 checkStatus);

// Application command 42 (SET_CLR_CARD_DETECT): argument 1 disconnects the card's pull-up on DAT3, 0 connects it.
// The call is repeated in each branch, which is what gets the unit loaded before the test.
void FUN_FFFF54A8(u32 disconnect)
{
    if (disconnect != 0) {
        FUN_FFFF4E00(DAT_FFF000B8, 1, 0);
    } else {
        FUN_FFFF4E00(DAT_FFF000B8, 0, 0);
    }
    FUN_FFFF3844(0x6A, 1);
}
