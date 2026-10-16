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

// Command 1 (SEND_OP_COND) with the argument 0x00100000; the 4-byte response (the card's OCR) goes to out.
void FUN_FFFF53AC(u8 *out)
{
    FUN_FFFF4E00(DAT_FFF000B8, 0, 0x10);
    FUN_FFFF3844(0x701, 0);
    if (DAT_FFF000C0->unk34 == 0) {
        FUN_FFFF49D8(DAT_FFF000B8, 0, out);
    }
}
