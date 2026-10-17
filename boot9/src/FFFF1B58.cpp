#include "types.h"

// One entry of the table at DAT_FFF01990 (0x2C bytes each): how a DMA channel moves data, as FUN_FFFF1CB4 sets it.
struct Unk_FFF01990 {
    u8 pad00[2];
    u8 ccr[4];
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
    u8 pad1F;
    u8 unk20;
    u8 unk21;
    u8 pad22[2];
    u32 unk24;
    u8 pad28[4];
};

extern Unk_FFF01990 DAT_FFF01990[];

// Gives the four channels their default settings: bursts of one 8-byte beat each way, worked out as FUN_FFFF1CB4 does.
// The larger burst is chosen the same way too: armcc folds the comparison but loads unk0C again, as the image does, and
// with that expression the registers holding 0 and 8 come out as in the image.
void FUN_FFFF1B58()
{
    for (s32 i = 0; i < 4; i++) {
        Unk_FFF01990 *p = &DAT_FFF01990[i];
        p->ccr[0] = 7;
        p->ccr[1] = 0xC3;
        p->ccr[2] = 0xC1;
        p->ccr[3] = 0;
        p->unk08 = 8;
        p->unk09 = 8;
        p->unk0A = 1;
        p->unk0B = 1;
        p->unk0C = p->unk08 * p->unk0A;
        p->unk10 = p->unk09 * p->unk0B;
        p->unk14 = p->unk0C < p->unk10 ? p->unk10 : p->unk0C;
        p->unk06 = 8;
        p->unk18 = 0;
        p->unk1A = 0;
        p->unk24 = 0;
        p->unk1C = 0;
        p->unk1D = 1;
        p->unk1E = 0;
        p->unk20 = 0;
        p->unk21 = 0;
    }
}
