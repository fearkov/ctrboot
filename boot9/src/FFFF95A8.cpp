#include "types.h"

extern u32 DAT_FFF00618[4];

extern "C" void FUN_FFFF8AA0(u32 slot, u32 mode, const u32 *key);

void FUN_FFFF95A8()
{
    FUN_FFFF8AA0(0x3F, 5, DAT_FFF00618);
}
