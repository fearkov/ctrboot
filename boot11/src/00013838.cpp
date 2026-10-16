#include "types.h"

extern "C" void FUN_000137CC(u32 which);
extern "C" void FUN_00013768(u32 which, u32 flag);
extern "C" u8 FUN_00013580(u32 which);

struct Unk_00013B58 {
    u32 unk0;
    u8 unk4;
    u8 pad5[3];
};

extern Unk_00013B58 DAT_00013B58[];

u8 FUN_00013838(u32 dev)
{
    FUN_000137CC(DAT_00013B58[dev].unk0);
    FUN_00013768(DAT_00013B58[dev].unk0, 1);
    return FUN_00013580(DAT_00013B58[dev].unk0);
}
