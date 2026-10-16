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
