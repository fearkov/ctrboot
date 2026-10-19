#include "types.h"

// One entry of the table at DAT_1FFE83C0 (0x2C bytes each): how a DMA channel moves data (FUN_00011F74 reads unk1C,
// whether the channel interrupts). boot9 has the same table for its four channels (DAT_FFF01990, FUN_FFFF1B58).
struct Unk_1FFE83C0 {
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

extern Unk_1FFE83C0 DAT_1FFE83C0[];

// Gives the eight channels their default settings: bursts of one 8-byte beat each way. unk0C, unk10 and unk14 are
// worked out from the burst fields as in boot9's FUN_FFFF1B58: armcc folds them all to 8, but only with these
// expressions do the registers holding 0 and 8 come out as in the image (stored as constants, r2 and r3 swap).
void FUN_000123B4()
{
    for (s32 i = 0; i < 8; i++) {
        Unk_1FFE83C0 *p = &DAT_1FFE83C0[i];
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
