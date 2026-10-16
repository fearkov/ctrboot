#include "types.h"

struct Unk_FFFF3EB8 {
    u8 unk0[4];
    u16 unk4;
    u16 unk6;
    u16 unk8;
};

void FUN_FFFF3EB8(Unk_FFFF3EB8 *p, u16 *a, u8 *b, u8 *c)
{
    *a = ((p->unk8 & 3) << 10) | (p->unk6 >> 6);
    *b = (p->unk4 & 0x3FF) >> 7;
    *c = (p->unk8 >> 8) & 0xF;
}
