#include "types.h"

struct Unk_FFF000C0
{
    u8 pad00[0x34];
    u32 unk34;
};

extern "C" void FUN_FFFF4E00(u32 unit, u16 low, u16 high);
extern "C" void FUN_FFFF3844(u32 command, u32 flag);
extern "C" void FUN_FFFF49D8(u32 unit, u32 mode, u8 *out);
extern u32 DAT_FFF000B8;
extern Unk_FFF000C0 *DAT_FFF000C0;

// ACMD41 (SD_SEND_OP_COND) for 3.2-3.3V, with the HCS bit when asked; keeps the OCR from the response.
void FUN_FFFF529C(bool hcs, u8 *ocr)
{
    if (hcs)
    {
        FUN_FFFF4E00(DAT_FFF000B8, 0, 0x4010);
    }
    else
    {
        FUN_FFFF4E00(DAT_FFF000B8, 0, 0x10);
    }
    FUN_FFFF3844(0x69, 0);
    if (DAT_FFF000C0->unk34 == 0)
    {
        FUN_FFFF49D8(DAT_FFF000B8, 0, ocr);
    }
}
