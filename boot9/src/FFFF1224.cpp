#include "types.h"

struct Unk_FFF01990 {
    u8 pad00[0x1c];
    u8 unk1c;
    u8 unk1d;
    u8 pad1e[6];
    u32 unk24;
    u8 pad28[4];
};

extern Unk_FFF01990 DAT_FFF01990[];

u8 FUN_FFFF1224(s32 index, u8 value)
{
    Unk_FFF01990 *entry = &DAT_FFF01990[index];
    u8 old = entry->unk1d;
    entry->unk1d = value;
    return old;
}
