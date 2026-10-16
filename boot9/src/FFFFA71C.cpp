#include "types.h"

struct Unk_FFFF4740 {
    u8 unk00[0x14];
    u32 *unk14;
};

extern "C" void FUN_FFFF4740(Unk_FFFF4740 *p);

// Points the field at +0x14 into the object itself (0x2C bytes from its start), then hands the object
// to FUN_FFFF4740.
void FUN_FFFFA71C(Unk_FFFF4740 *p)
{
    p->unk14 = (u32 *)((u8 *)p + 0x2C);
    FUN_FFFF4740(p);
}
