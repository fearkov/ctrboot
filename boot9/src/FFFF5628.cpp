// Built for space like the rest of the SD/MMC code, as FUN_FFFF5AA4 which has the same shape: the 8 bytes of outgoing
// stack arguments are allocated by pushing r2 and r3 along with r4-r6 (what -Ospace does; -Otime uses sub sp).
#pragma Ospace
#include "types.h"

// The callback is not in boot9.functions (it takes the same five arguments as FUN_FFFF3EDC): it is reached by its
// address, with the Thumb bit set. Call it as FUN_FFFF3970 once the list has it.
extern u8 DAT_FFFF3970;

extern "C" u32 FUN_FFFF3784(u32 (*op)(u32, u32, u32, u32, void *), u32 first, u32 last, u32 sector, u32 count,
                            void *buf);

u32 FUN_FFFF5628(u32 first, u32 last, u32 sector, u32 count, void *buf)
{
    return FUN_FFFF3784((u32 (*)(u32, u32, u32, u32, void *))((u32)&DAT_FFFF3970 + 1), first, last, sector, count, buf);
}
