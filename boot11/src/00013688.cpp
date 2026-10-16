#include "types.h"

extern "C" void FUN_000137CC(u32 which);
extern "C" void FUN_00013734(u32 which, u8 data);
extern "C" void FUN_00013748(u32 which);
extern "C" u32 FUN_000135A4(u32 which);

struct Unk_00013B58 {
    u32 unk0;
    u8 unk4;
    u8 pad5[3];
};

extern Unk_00013B58 DAT_00013B58[];

u32 FUN_00013688(u32 dev)
{
    FUN_000137CC(DAT_00013B58[dev].unk0);
    FUN_00013734(DAT_00013B58[dev].unk0, DAT_00013B58[dev].unk4 | 1);
    FUN_00013748(DAT_00013B58[dev].unk0);
    return FUN_000135A4(DAT_00013B58[dev].unk0);
}
