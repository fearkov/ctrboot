#include "types.h"

// The sector loop that FUN_FFFF55F8 and FUN_FFFF5610 share: calls op(sector, count, buf) on chunks of sectors.
extern "C" u32 FUN_FFFF36D8(u32 mode, u32 (*op)(u32, u32, void *), u32 sector, u32 count, void *buf);

// The callback (the function right after FUN_FFFF3900) is not in boot9.functions: it is reached by its address, with
// the Thumb bit set. Call it as FUN_FFFF3930 once the list has it.
extern u8 DAT_FFFF3930;

u32 FUN_FFFF5610(u32 sector, u32 count, void *buf)
{
    return FUN_FFFF36D8(1, (u32 (*)(u32, u32, void *))((u32)&DAT_FFFF3930 + 1), sector, count, buf);
}
