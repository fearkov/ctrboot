// Built for space like FUN_FFFF5AA4, whose twin this is (the 8 bytes of outgoing stack arguments are allocated by
// push {r2-r6, lr}, which -Otime does not do): the same wrapper around FUN_FFFF3784 with the callback at 0xFFFF4474
// (the twin of FUN_FFFF3EDC) instead of FUN_FFFF3EDC.
#pragma Ospace
#include "types.h"

// Thumb entry (bit 0 set) of the callback at 0xFFFF4474, which boot9.functions does not list.
extern u8 DAT_FFFF4475;
extern "C" u32 FUN_FFFF3784(u32 (*op)(u32, u32, u32, u32, void *), u32 first, u32 last, u32 sector, u32 count,
                            void *buf);

u32 FUN_FFFF5D04(u32 first, u32 last, u32 sector, u32 count, void *buf)
{
    return FUN_FFFF3784((u32 (*)(u32, u32, u32, u32, void *))&DAT_FFFF4475, first, last, sector, count, buf);
}
