#include "types.h"

struct Unk_FFFF5CD0
{
    u8 pad00[0xc4];
    u8 unkC4;
};

extern "C" void FUN_FFFF4E68(u32 unit, u32 value);

void FUN_FFFF5CD0(u32 unit, Unk_FFFF5CD0 *cfg)
{
    u32 value;
    if (cfg->unkC4 & 2)
    {
        value = 0;
    }
    else
    {
        value = 1;
    }
    FUN_FFFF4E68(unit, value);
}
