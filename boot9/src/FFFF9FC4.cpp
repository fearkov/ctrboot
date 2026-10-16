#include "types.h"

struct Unk_FFF00240 {
    u16 unk0;
    u8 unk2;
    u8 unk3;
    u8 unk4;
    u8 unk5;
    u8 unk6;
    u8 unk7;
    u8 unk8;
    u8 unk9;
};
extern Unk_FFF00240 DAT_FFF00240;

// One entry of the table at DAT_FFF01990.
struct Unk_FFF01990 {
    u8 unk0[6];
    u16 unk6;
    u8 unk8[0x24];
};

typedef u32 (*Unk_Callback)(u32, u32, u32, u32);

extern "C" void FUN_FFFF1E10(u32 index);
extern "C" void FUN_FFFFAE58();
extern "C" void FUN_FFFF1A84(u32 index, void *dst);
extern "C" void FUN_FFFF1D64(u32 index, const void *src);
extern "C" Unk_Callback FUN_FFFF11FC(s32 index, Unk_Callback callback);
extern "C" void FUN_FFFF14EC(u32 index, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6);

void FUN_FFFF9FC4(u32 a, u32 b, u32 c, u32 d, Unk_Callback callback)
{
    Unk_FFF01990 entry;
    FUN_FFFF1E10(DAT_FFF00240.unk5);
    FUN_FFFFAE58();
    FUN_FFFF1A84(DAT_FFF00240.unk5, &entry);
    entry.unk6 = DAT_FFF00240.unk7;
    FUN_FFFF1D64(DAT_FFF00240.unk5, &entry);
    DAT_FFF00240.unk0 |= 0x500;
    if (callback == 0) {
        *(volatile u32 *)0x1000A000 = DAT_FFF00240.unk0;
    }
    FUN_FFFF11FC(DAT_FFF00240.unk5, callback);
    FUN_FFFF14EC(DAT_FFF00240.unk5, 0x1000A080, a, b, c, d, 7);
}
