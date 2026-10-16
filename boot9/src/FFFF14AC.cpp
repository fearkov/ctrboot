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
extern "C" void FUN_FFFF13D8(s32 index, u32 arg);

u32 FUN_FFFF14AC(s32 index, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5)
{
    Unk_FFF01990 *entry = &DAT_FFF01990[index];
    if (entry->unk24 != 0) {
        if (entry->unk1d != 0) {
            FUN_FFFF13D8(index, a5);
        }
        if (entry->unk24(a1, a2, a3, a4) == 0) {
            return 0;
        }
    }
    return 1;
}
