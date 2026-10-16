#include "types.h"

typedef u32 (*Unk_Callback)(u32, u32, u32, u32);

struct Unk_FFF01990 {
    u8 pad00[0x1c];
    u8 unk1c;
    u8 unk1d;
    u8 pad1e[6];
    Unk_Callback unk24;
    u8 pad28[4];
};

extern Unk_FFF01990 DAT_FFF01990[];

Unk_Callback FUN_FFFF11FC(s32 index, Unk_Callback callback)
{
    Unk_FFF01990 *entry = &DAT_FFF01990[index];
    Unk_Callback old = entry->unk24;
    entry->unk24 = callback;
    return old;
}
