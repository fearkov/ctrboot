#include "types.h"

extern u8 DAT_FFF01728[];

extern "C" void FUN_FFFF8694(u64 *block);
extern "C" void FUN_FFFF86A8(u32 *block);
extern "C" void FUN_FFFF4740(u8 *cmd);

// The same as FUN_FFFF9684 for the card command 0x3C: builds it at 0xFFF01728 with its response pointer (+0x14) set
// to +0x2C, FUN_FFFF8694 filling bits 32-55 and FUN_FFFF86A8 the low word, and issues it with FUN_FFFF4740.
void FUN_FFFF96B8()
{
    u8 *cmd = DAT_FFF01728;
    *(u8 **)(cmd + 0x14) = cmd + 0x2C;
    *(__packed u64 *)cmd = 0x3C00000000000000ULL;
    FUN_FFFF8694((u64 *)cmd);
    FUN_FFFF86A8((u32 *)cmd);
    FUN_FFFF4740(cmd);
}
