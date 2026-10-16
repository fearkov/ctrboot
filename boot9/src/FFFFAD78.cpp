#include "types.h"

extern "C" void FUN_FFFF1BDC(u8 value);

struct Unk_FFF00240 {
    u8 unk0[5];
    u8 unk5;
};
extern Unk_FFF00240 DAT_FFF00240;

void FUN_FFFFAD78()
{
    FUN_FFFF1BDC(DAT_FFF00240.unk5);
}
