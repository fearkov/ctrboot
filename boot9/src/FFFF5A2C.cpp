#include "types.h"

extern u32 DAT_FFF000B8;

extern "C" u32 FUN_FFFF4A98(u32 unit, u32 type);

// Whether the device with this id is there: id 0x200 is the one that can be missing, its slot is asked; any other id
// always is.
u32 FUN_FFFF5A2C(u32 id)
{
    if (id == 0x200) {
        return FUN_FFFF4A98(DAT_FFF000B8, 0);
    }
    return 1;
}
