// One translation unit with FUN_FFFF5A48 (not inlined): armcc then knows its callee needs no stack alignment, so
// FUN_FFFF5A74 saves nothing but lr.
#pragma no_inline
#include "types.h"

struct Unk_FFFF5A48
{
    u8 unk00[0x10];
    u8 unk10;
};

bool FUN_FFFF5A48(Unk_FFFF5A48 *p)
{
    return (p->unk10 & 0xf) == 1;
}

// The same test of the switch status, made after the switch.
bool FUN_FFFF5A74(Unk_FFFF5A48 *p)
{
    return FUN_FFFF5A48(p);
}
