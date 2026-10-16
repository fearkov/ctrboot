#include "types.h"

struct Unk_FFF001A8 {
    u8 unk0;
    u8 pad1[3];
    void *unk4;
    u32 unk8;
};

extern Unk_FFF001A8 DAT_FFF001A8;
extern u32 DAT_FFF00150;
extern u32 DAT_FFF00154;
extern u32 DAT_FFF00158;

extern "C" u32 FUN_FFFF1BA8(u32 index);
extern "C" u32 FUN_FFFF8950();
extern "C" u32 FUN_FFFFAD58();
extern "C" void FUN_FFFF89E4();
extern "C" void FUN_FFFFAE3C();
extern "C" void FUN_FFFF1C94(u32 index, u32 first, u32 second);
extern "C" void FUN_FFFF1C84(u32 index, u32 value);
extern "C" void FUN_FFFF1CA4(u32 index, u32 value);
extern "C" void FUN_FFFF1C2C(u32 index, u32 a1, u32 a2, u32 a3, void (*callback)(u32), u32 callbackArg, u32 a6);
extern "C" void FUN_FFFF1BF0(u32 index, u32 a1, u32 a2, u32 a3, void (*callback)(u32), u32 callbackArg, u32 a6);
extern "C" void FUN_FFFFACC8();
extern "C" void FUN_FFFFACAC(u16 value);
extern "C" void FUN_FFFFAD88();
extern "C" void FUN_FFFFADA0();
extern "C" void FUN_FFFF8A00(u32 mode, u32 a, u32 b, u32 blkcnt, u32 blklen, u32 c, u32 d);

u32 FUN_FFFF3FA0(u32 fifo)
{
    if (FUN_FFFF1BA8(DAT_FFF00150) != 0) {
        return 0x20000;
    }
    if (FUN_FFFF1BA8(DAT_FFF00154) != 0) {
        return 0x20000;
    }
    if (FUN_FFFF1BA8(DAT_FFF00158) != 0) {
        return 0x20000;
    }
    if (FUN_FFFF8950() != 0) {
        return 0x80000;
    }
    if (FUN_FFFFAD58() != 0) {
        return 0x100000;
    }
    FUN_FFFF89E4();
    FUN_FFFFAE3C();
    FUN_FFFF1C94(DAT_FFF00158, 0, 0);
    FUN_FFFF1C84(DAT_FFF00158, 0x40000);
    FUN_FFFF1CA4(DAT_FFF00158, 0x10);
    FUN_FFFF1C2C(DAT_FFF00158, 0x1000A080, (u32)DAT_FFF001A8.unk4, DAT_FFF001A8.unk8, 0, 0, 0x0B000000);
    FUN_FFFF1C94(DAT_FFF00154, 0, 0);
    FUN_FFFF1C84(DAT_FFF00154, 0x30000);
    FUN_FFFF1CA4(DAT_FFF00154, 8);
    FUN_FFFF1BF0(DAT_FFF00154, 0x1000900C, 0x1000A080, DAT_FFF001A8.unk8, 0, 0, 0x0F000010);
    FUN_FFFF1C94(DAT_FFF00150, 0, 0);
    FUN_FFFF1C84(DAT_FFF00150, 0x30000);
    FUN_FFFF1CA4(DAT_FFF00150, 8);
    FUN_FFFF1BF0(DAT_FFF00150, fifo, 0x10009008, DAT_FFF001A8.unk8, 0, 0, 0x0F000008);
    FUN_FFFFACC8();
    FUN_FFFFACAC(0x404);
    if (DAT_FFF001A8.unk0) {
        FUN_FFFFAD88();
    } else {
        FUN_FFFFADA0();
    }
    FUN_FFFF8A00(2, 5, 5, 0, DAT_FFF001A8.unk8 >> 4, 0, 0);
    return 0;
}
