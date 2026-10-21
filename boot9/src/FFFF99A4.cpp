// The byte at 0xFFF000E9 is volatile: armcc may not move its load, so the code before it is scheduled on its own,
// as in the dump (with a plain field armcc loads the word at 0xFFF0066C late). The seed table is a member of the
// struct at 0xFFF000E8, so armcc reaches the struct as the table's literal minus 0x34.
#include "types.h"

struct Unk_080F8000 {
    u8 pad00[0x12];
    u16 unk12;
};
extern Unk_080F8000 DAT_080F8000;

struct Unk_FFF0064C {
    u8 pad00[0x20];
    u32 unk20;
};
extern Unk_FFF0064C DAT_FFF0064C;

// The KEY2 seed parts: unk00 the top byte of seed Y, unk01 the second byte of seed X, unk1C the low word of seed Y,
// unk34 the low byte of seed X for each value of the header's seed select.
struct Unk_FFF000E8 {
    u8 unk00;
    volatile u8 unk01;
    u8 pad02[0x1A];
    u32 unk1C;
    u8 pad20[0x14];
    u8 unk34[8];
};
extern Unk_FFF000E8 DAT_FFF000E8;

// The card controller: unk04 the control word, unk10 and unk14 the low words of seeds X and Y, unk18 and unk1A
// their top bytes.
struct Unk_10164000 {
    u8 pad00[4];
    volatile u32 unk04;
    u8 pad08[8];
    volatile u32 unk10;
    volatile u32 unk14;
    volatile u8 unk18;
    u8 pad19;
    volatile u8 unk1A;
};
extern Unk_10164000 DAT_10164000;

struct Unk_FFF01770 {
    u32 unk00;
    u32 unk04;
};
extern Unk_FFF01770 DAT_FFF01770;

extern "C" void FUN_FFFF35A0();

// Loads the KEY2 seeds into the card controller and applies them: seed X is the low 24 bits of the word at
// 0xFFF0066C, then the byte at 0xFFF000E9, then the table byte that bits 8-10 of the card header's halfword at
// 0x080F8012 select; seed Y is the word at 0xFFF00104 under the byte at 0xFFF000E8. Then sets bits 13 and 14 of
// the word at 0xFFF01774.
void FUN_FFFF99A4()
{
    u32 key = DAT_FFF0064C.unk20;
    u32 select = (DAT_080F8000.unk12 >> 8) & 7;
    u8 *table = DAT_FFF000E8.unk34;
    u32 low = table[select];
    u32 high = (key << 15) | (DAT_FFF000E8.unk01 << 8);
    u32 xLow = low | high;
    u8 xTop = (key & 0xFFFFFF) >> 17;
    u32 yLow = DAT_FFF000E8.unk1C;
    u8 yTop = DAT_FFF000E8.unk00;
    FUN_FFFF35A0();
    DAT_10164000.unk10 = xLow;
    DAT_10164000.unk18 = xTop;
    DAT_10164000.unk14 = yLow;
    DAT_10164000.unk1A = yTop;
    DAT_10164000.unk04 = 0x2000E000;
    FUN_FFFF35A0();
    Unk_FFF01770 *flags = &DAT_FFF01770;
    flags->unk04 |= 0x6000;
}
