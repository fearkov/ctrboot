#include "types.h"

struct Unk_FFF01990 {
    u8 pad00[2];
    volatile u8 ccr[4];
    u16 unk06;
    u8 unk08;
    u8 unk09;
    u8 unk0A;
    u8 unk0B;
    u32 unk0C;
    u32 unk10;
    u32 unk14;
    u16 unk18;
    u16 unk1A;
    u8 unk1C;
    u8 unk1D;
    u8 unk1E;
    u8 pad1F[5];
    u32 unk24;
    u8 pad28[4];
};

extern Unk_FFF01990 DAT_FFF01990[];

// Sets the source and destination burst sizes and lengths in DMA channel index's control register image (the
// DMA-330's CCR), keeps the bytes per burst of each side and the larger of the two, rounds size up to whole bursts,
// and resets the channel's state.
void FUN_FFFF1CB4(u32 index, u32 size, s32 srcBurstSize, s32 srcBurstLen, s32 dstBurstSize, s32 dstBurstLen, u16 a6,
                  u16 a7)
{
    u32 ccr = DAT_FFF01990[index].ccr[0] & ~(7 << 1);
    DAT_FFF01990[index].ccr[0] = ccr;
    DAT_FFF01990[index].ccr[0] |= srcBurstSize << 1;
    DAT_FFF01990[index].ccr[0] = (DAT_FFF01990[index].ccr[0] & 0x0F) | (srcBurstLen << 4);
    DAT_FFF01990[index].ccr[1] = (DAT_FFF01990[index].ccr[1] & 0x7F) | (dstBurstSize << 7);
    DAT_FFF01990[index].ccr[2] &= ~3;
    u8 hi = dstBurstSize >> 1;
    DAT_FFF01990[index].ccr[2] |= hi;
    DAT_FFF01990[index].ccr[2] &= ~(0xF << 2);
    DAT_FFF01990[index].ccr[2] |= dstBurstLen << 2;

    DAT_FFF01990[index].unk08 = 1 << srcBurstSize;
    DAT_FFF01990[index].unk09 = 1 << dstBurstSize;
    DAT_FFF01990[index].unk0A = srcBurstLen + 1;
    DAT_FFF01990[index].unk0B = dstBurstLen + 1;
    DAT_FFF01990[index].unk0C = DAT_FFF01990[index].unk08 * DAT_FFF01990[index].unk0A;
    DAT_FFF01990[index].unk10 = DAT_FFF01990[index].unk09 * DAT_FFF01990[index].unk0B;
    u32 burst = DAT_FFF01990[index].unk0C < DAT_FFF01990[index].unk10 ? DAT_FFF01990[index].unk10
                                                                       : DAT_FFF01990[index].unk0C;
    DAT_FFF01990[index].unk14 = burst;
    u32 last = size - 1;
    DAT_FFF01990[index].unk06 = (burst + last) & ~(burst - 1);
    DAT_FFF01990[index].unk18 = a6;
    DAT_FFF01990[index].unk1A = a7;
    DAT_FFF01990[index].unk24 = 0;
    DAT_FFF01990[index].unk1C = 0;
    DAT_FFF01990[index].unk1D = 1;
    DAT_FFF01990[index].unk1E = 0;
}
