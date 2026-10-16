#include "types.h"

struct Unk_FFF000C0 {
    u8 pad00[0x34];
    u32 unk34;
};

extern u32 DAT_FFF000B8;
extern Unk_FFF000C0 *DAT_FFF000C0;

extern "C" void FUN_FFFF4E00(u32 unit, u16 low, u16 high);
extern "C" void FUN_FFFF3844(u32 command, u32 checkStatus);
extern "C" void FUN_FFFF49D8(u32 unit, u32 mode, u8 *out);

// Command 3 (SEND_RELATIVE_ADDR): the card's new address is the upper half of its response.
void FUN_FFFF53E8(u16 *rca)
{
    u32 response;
    FUN_FFFF4E00(DAT_FFF000B8, 0, 0);
    FUN_FFFF3844(3, 0);
    if (DAT_FFF000C0->unk34 == 0) {
        FUN_FFFF49D8(DAT_FFF000B8, 0, (u8 *)&response);
        *rca = response >> 16;
    }
}
