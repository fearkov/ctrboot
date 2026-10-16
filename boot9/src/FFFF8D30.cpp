#include "types.h"

struct Unk_FFF000C8_14 {
    u8 unk00[0x0c];
    u32 unk0c;
};

struct Unk_FFF000C8 {
    u32 unk00;
    u32 unk04;
    u32 unk08;
    u32 unk0c;
    u32 unk10;
    struct Unk_FFF000C8_14 *unk14;
};

extern struct Unk_FFF000C8 DAT_FFF000C8;

u32 FUN_FFFF8D30()
{
    struct Unk_FFF000C8_14 *p = DAT_FFF000C8.unk14;
    return p ? p->unk0c : 0;
}
