#include "types.h"

struct Unk_FFFF5A96
{
    u8 unk00[0xd];
    u8 unkD;
};

u32 FUN_FFFF5A96(Unk_FFFF5A96 *p)
{
    if ((s32)((u32)p->unkD << 30) < 0)
    {
        return 1;
    }
    return 0;
}
