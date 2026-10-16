#include "types.h"

struct Unk_FFFF5CE6
{
    u8 unk00[0xb];
    u8 unkB;
};

extern "C" void FUN_FFFF41E8(u32 unit, Unk_FFFF5CE6 *cfg);

void FUN_FFFF5CE6(u32 unit, Unk_FFFF5CE6 *cfg)
{
    FUN_FFFF41E8(unit, cfg);
}
