// Built for space: room for the 12 bytes of outgoing stack arguments comes from pushing r1-r3 along
// with r4 and r5 (-Otime allocates it with sub sp and checks the pointer before the push).
#pragma Ospace
#include "types.h"

extern "C" void FUN_FFFF8A00(u32 a, u32 b, u32 c, u32 d, u32 e, u32 f, u32 g);
extern "C" void FUN_FFFF8C08(u32 *dst, u32 src, u32 size);

// Passes the 0x100 bytes at 0x10012000 through the AES engine (FUN_FFFF8A00 sets it up) into dst.
u32 FUN_FFFFAC00(u32 *dst)
{
    if (dst == 0)
        return 0;
    FUN_FFFF8A00(4, 5, 5, 0, 0x10, 0, 0);
    FUN_FFFF8C08(dst, 0x10012000, 0x100);
    return 1;
}
