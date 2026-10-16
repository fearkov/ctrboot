#include "types.h"

extern "C" u64 FUN_000125E4();
extern u64 DAT_1FFE8E50[];

void FUN_000137B4(u32 which)
{
    DAT_1FFE8E50[which] = FUN_000125E4();
}
