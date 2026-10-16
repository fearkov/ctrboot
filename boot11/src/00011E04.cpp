#include "types.h"

struct Unk_00011E04 {
    u16 unk0;
    u16 unk2;
    u16 unk4;
};

extern "C" void FUN_00011E30(u32 which);
extern volatile Unk_00011E04 DAT_10161000;
extern volatile Unk_00011E04 DAT_10144000;

void FUN_00011E04()
{
    FUN_00011E30(0);
    DAT_10161000.unk2 = 2;
    DAT_10161000.unk4 = 0x500;
    FUN_00011E30(1);
    DAT_10144000.unk2 = 2;
    DAT_10144000.unk4 = 0x500;
}
