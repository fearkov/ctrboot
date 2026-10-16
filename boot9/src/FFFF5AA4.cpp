#include "types.h"

// FUN_FFFF3784 splits the transfer into chunks of at most 0x7FF sectors and calls op(first, last, sector, count, buf)
// for each, passing first only on the first chunk and last only on the last one (0 otherwise).
extern "C" u32 FUN_FFFF3EDC(u32 first, u32 last, u32 sector, u32 count, void *buf);
extern "C" u32 FUN_FFFF3784(u32 (*op)(u32, u32, u32, u32, void *), u32 first, u32 last, u32 sector, u32 count,
                            void *buf);

u32 FUN_FFFF5AA4(u32 first, u32 last, u32 sector, u32 count, void *buf)
{
    return FUN_FFFF3784(FUN_FFFF3EDC, first, last, sector, count, buf);
}
