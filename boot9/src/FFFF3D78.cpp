#include "types.h"

extern u8 DAT_FFF00280[];
extern u8 DAT_FFF002E4[];

u8 *FUN_FFFF3D78(u32 id)
{
    switch (id) {
    case 0x200:
        return DAT_FFF00280;
    case 0x201:
        return DAT_FFF002E4;
    default:
        return 0;
    }
}
