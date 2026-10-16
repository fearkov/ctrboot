#include "types.h"

struct Unk_FFF00230
{
    u64 unk00;
    u16 unk08;
    u16 unk0A;
};

extern "C" void FUN_FFFF2064();
extern "C" u64 FUN_FFFF1F70();
extern "C" u16 FUN_FFFF4F94();
extern u32 DAT_FFF00074;
extern Unk_FFF00230 DAT_FFF00230;

// One-time setup: runs once (DAT_FFF00074 is the done flag) and stores the values it reads in DAT_FFF00230.
void FUN_FFFF4F64()
{
    Unk_FFF00230 *info = &DAT_FFF00230;
    if (DAT_FFF00074 == 0)
    {
        DAT_FFF00074 = 1;
        FUN_FFFF2064();
        info->unk00 = FUN_FFFF1F70();
        info->unk08 = FUN_FFFF4F94();
        info->unk0A = info->unk08;
    }
}
