#include "types.h"

struct Unk_FFF000C0 {
    u8 pad00[0x34];
    u32 unk34;
};

extern u32 DAT_FFF000B8;
extern Unk_FFF000C0 *DAT_FFF000C0;

extern "C" void FUN_FFFF4E00(u32 unit, u16 low, u16 high);
extern "C" void FUN_FFFF3844(u32 command, u32 checkStatus);
extern "C" u32 FUN_FFFF4A86(u32 unit);

// Command 12 (STOP_TRANSMISSION), then waits for the card to stop being busy (or for an error).
void FUN_FFFF54F0()
{
    FUN_FFFF4E00(DAT_FFF000B8, 0, 0);
    FUN_FFFF3844(0xC, 1);
    while (FUN_FFFF4A86(DAT_FFF000B8) != 0) {
        if (DAT_FFF000C0->unk34 != 0) {
            break;
        }
    }
}
