#include "types.h"

struct Unk_FFFF5A8A
{
    u8 unk00[0xc4];
    u8 unkC4;
};

bool FUN_FFFF5A8A(Unk_FFFF5A8A *p)
{
    return (p->unkC4 & 3) != 0;
}
