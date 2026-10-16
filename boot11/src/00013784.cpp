// The register select lives in a small inline helper: written inline in the function,
// armcc puts the loaded bus number in r0 and the register address in r1, the other way
// round from the dump.
#include "types.h"

extern "C" void FUN_000137CC(u32 which);
extern "C" void FUN_000137B4(u32 which);
extern volatile u8 DAT_10161001;
extern volatile u8 DAT_10144001;

struct Unk_00013B58 {
    u32 unk0;
    u8 unk4;
    u8 pad5[3];
};

extern Unk_00013B58 DAT_00013B58[];

static inline void write(u32 which, u8 v)
{
    *((which == 0) ? &DAT_10161001 : &DAT_10144001) = v;
}

void FUN_00013784(u32 dev)
{
    write(DAT_00013B58[dev].unk0, 0xC5);
    FUN_000137CC(DAT_00013B58[dev].unk0);
    FUN_000137B4(DAT_00013B58[dev].unk0);
}
