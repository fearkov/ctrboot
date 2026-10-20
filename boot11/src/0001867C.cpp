#include "types.h"

struct Unk_10202000 {
    u32 unk0;
    u32 unk4;
    u32 unk8;
};

extern volatile Unk_10202000 DAT_10202000;

// Reads bits 0, 8 and 9 of 0x10202008 into a, b and c, skipping the null pointers.
void FUN_0001867C(u32* a, u32* b, u32* c)
{
    if (a)
        *a = DAT_10202000.unk8 & 1;
    if (b)
        *b = (DAT_10202000.unk8 >> 8) & 1;
    if (c)
        *c = (DAT_10202000.unk8 >> 9) & 1;
}
