// The first check reaches DAT_FFF00150 through a pointer local: naming the global there too, armcc keeps its address
// in a register for the whole function and hoists the poll limit out of the loop, where the ROM keeps the address of
// DAT_FFF00154 instead and loads the limit inside the loop.
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
extern u32 DAT_FFF0015C;

extern "C" u32 FUN_FFFF1BA8(u32 index);
extern "C" u32 FUN_FFFF1BBC(u32 index);
extern "C" u32 FUN_FFFF8950();
extern "C" u32 FUN_FFFFAD58();
extern "C" void FUN_FFFF89E4();
extern "C" void FUN_FFFFAE3C();
extern "C" void FUN_FFFF1CB4(s32 index, s32 size, s32 srcBurstSize, s32 srcBurstLen, s32 dstBurstSize,
                             s32 dstBurstLen, s32 a6, s32 a7);
extern "C" void FUN_FFFF14EC(u32 index, u32 a, u32 b, u32 n, void (*cb)(void *), void *arg, u32 c);
extern "C" bool FUN_FFFF1BDC(u32 index);
extern "C" void FUN_FFFF1DBC(u32 index);
extern "C" void FUN_FFFF1C94(u32 index, u32 first, u32 second);
extern "C" void FUN_FFFF1C84(u32 index, u32 value);
extern "C" void FUN_FFFF1CA4(u32 index, u32 value);
extern "C" void FUN_FFFF1BF0(u32 index, u32 a1, u32 a2, u32 a3, void (*callback)(u32), u32 callbackArg, u32 a6);
extern "C" void FUN_FFFFACC8();
extern "C" void FUN_FFFFACAC(u16 value);
extern "C" void FUN_FFFFAD88();
extern "C" void FUN_FFFFADA0();
extern "C" void FUN_FFFF8A00(u32 mode, u32 a, u32 b, u32 blkcnt, u32 blklen, u32 c, u32 d);

// FIFO callback installed by FUN_FFFF4474, the FUN_FFFF3FA0 of the other DMA engine: fails with 0x20000 if one of the
// two NDMA channels is still busy, 0x40000 if the channel DAT_FFF0015C of the other engine is not stopped, 0x80000 if
// AES is busy and 0x100000 if SHA is busy. Otherwise starts that channel copying the SHA FIFO into the buffer (with
// bigger bursts when the buffer is 8-byte aligned) and polls until it reaches state 7; after 0x28E971 polls it stops
// the channel and returns 0x1000. Then chains the NDMA channels (AES output FIFO into the SHA FIFO, controller FIFO
// into the AES input FIFO) and starts AES on the whole transfer.
u32 FUN_FFFF4538(volatile u32 *fifo)
{
    u32 *inChannel = &DAT_FFF00150;
    if (FUN_FFFF1BA8(*inChannel) != 0) {
        return 0x20000;
    }
    if (FUN_FFFF1BA8(DAT_FFF00154) != 0) {
        return 0x20000;
    }
    if (FUN_FFFF1BBC(DAT_FFF0015C) != 0) {
        return 0x40000;
    }
    if (FUN_FFFF8950() != 0) {
        return 0x80000;
    }
    if (FUN_FFFFAD58() != 0) {
        return 0x100000;
    }
    FUN_FFFF89E4();
    FUN_FFFFAE3C();
    if (((u32)DAT_FFF001A8.unk4 & 7) == 0) {
        FUN_FFFF1CB4(DAT_FFF0015C, 0x40, 2, 0xF, 3, 7, 0, 0);
    } else {
        FUN_FFFF1CB4(DAT_FFF0015C, 0x40, 2, 0xF, 2, 0xF, 0, 0);
    }
    FUN_FFFF14EC(DAT_FFF0015C, 0x1000A080, (u32)DAT_FFF001A8.unk4, DAT_FFF001A8.unk8, 0, 0, 7);
    u32 i = 0;
    while (!FUN_FFFF1BDC(DAT_FFF0015C)) {
        if (++i > 0x28E970) {
            FUN_FFFF1DBC(DAT_FFF0015C);
            return 0x1000;
        }
    }
    FUN_FFFF1C94(DAT_FFF00154, 0, 0);
    FUN_FFFF1C84(DAT_FFF00154, 0x30000);
    FUN_FFFF1CA4(DAT_FFF00154, 8);
    FUN_FFFF1BF0(DAT_FFF00154, 0x1000900C, 0x1000A080, DAT_FFF001A8.unk8, 0, 0, 0x0F000010);
    FUN_FFFF1C94(DAT_FFF00150, 0, 0);
    FUN_FFFF1C84(DAT_FFF00150, 0x30000);
    FUN_FFFF1CA4(DAT_FFF00150, 8);
    FUN_FFFF1BF0(DAT_FFF00150, (u32)fifo, 0x10009008, DAT_FFF001A8.unk8, 0, 0, 0x0F000008);
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
