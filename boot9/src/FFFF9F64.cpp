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
extern volatile u32 DAT_1000A000;

extern "C" void FUN_FFFF1DFC(u32 index);
extern "C" void FUN_FFFF1E10(u32 index);
extern "C" void FUN_FFFF8C80();
extern "C" void FUN_FFFFAE58();
extern "C" void FUN_FFFF89A4(u32 index, u32 size, void (*callback)(u32), u32 callbackArg);

void FUN_FFFF9F64(u32 size)
{
    FUN_FFFF1DFC(DAT_FFF00240.unk8);
    FUN_FFFF1E10(DAT_FFF00240.unk5);
    FUN_FFFF8C80();
    FUN_FFFFAE58();
    DAT_FFF00240.unk0 &= ~0x504;
    DAT_1000A000 = DAT_FFF00240.unk0;
    FUN_FFFF89A4(DAT_FFF00240.unk8, size, 0, 0);
    DAT_FFF00240.unk0 |= 0x504;
}
