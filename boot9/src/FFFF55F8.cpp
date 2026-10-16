#include "types.h"

// The sector loop that FUN_FFFF55F8 and FUN_FFFF5610 share: calls op(sector, count, buf) on chunks of sectors.
extern "C" u32 FUN_FFFF36D8(u32 mode, u32 (*op)(u32, u32, void *), u32 sector, u32 count, void *buf);
extern "C" u32 FUN_FFFF3900(u32 sector, u32 count, void *buf);

u32 FUN_FFFF55F8(u32 sector, u32 count, void *buf)
{
    return FUN_FFFF36D8(0, FUN_FFFF3900, sector, count, buf);
}
