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

struct Unk_FFFFB0C0 {
    u32 unk0;
    u32 unk4;
    u32 unk8;
    u32 unkC;
};
extern Unk_FFFFB0C0 DAT_FFFFB0C0;

extern "C" void FUN_FFFF1DFC(u32 index);
extern "C" void FUN_FFFF8C80();
extern "C" void FUN_FFFFAE58();
extern "C" void FUN_FFFF89A4(u32 index, u32 size, void (*callback)(u32), u32 callbackArg);
extern "C" void FUN_FFFF1138(u32 mode, u32 index, u32 src, u32 dst, u32 a4, u32 size, void (*callback)(u32),
                             u32 callbackArg, Unk_FFFFB0C0 *entry, u32 a9, u32 flags);

void FUN_FFFF9E10(u32 dst, u32 size, void (*callback)(u32), u32 callbackArg)
{
    FUN_FFFF1DFC(DAT_FFF00240.unk8);
    FUN_FFFF1DFC(DAT_FFF00240.unk9);
    FUN_FFFF8C80();
    FUN_FFFFAE58();
    DAT_FFF00240.unk0 &= ~0x504;
    *(volatile u32 *)0x1000A000 = DAT_FFF00240.unk0;
    FUN_FFFF1138(3, DAT_FFF00240.unk9, 0x1000A080, dst, 0, size, callback, callbackArg, &DAT_FFFFB0C0, 0x0B000000,
                 0x80000000);
    FUN_FFFF89A4(DAT_FFF00240.unk8, size, 0, 0);
    DAT_FFF00240.unk0 |= 0x504;
}
