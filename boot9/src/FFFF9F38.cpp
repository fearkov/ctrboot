#include "types.h"

extern "C" void FUN_FFFFAE3C();
extern "C" void FUN_FFFF1D94(u32 index);
extern "C" void FUN_FFFF1DBC(u8 value);

struct Unk_FFF00240 {
    u8 unk0[5];
    u8 unk5;
    u8 unk6[2];
    u8 unk8;
};
extern Unk_FFF00240 DAT_FFF00240;

void FUN_FFFF9F38()
{
    Unk_FFF00240 *p = &DAT_FFF00240;
    FUN_FFFFAE3C();
    FUN_FFFF1D94(p->unk8);
    FUN_FFFF1DBC(p->unk5);
}
