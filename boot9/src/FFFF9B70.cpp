#include "types.h"

// The state of a block-ordered card read, which FUN_FFFF8520 continues.
struct Unk_FFF0068C {
    s32 unk00;
    u8 pad04[2];
    s16 unk06;
    u8 *unk08;
    s16 unk0C;
    s16 unk0E;
    s16 unk10;
};

struct Unk_FFF0064C {
    u8 pad00[0x20];
    u32 unk20;
    u8 pad24[0x1C];
    Unk_FFF0068C unk40;
};
extern Unk_FFF0064C DAT_FFF0064C;

struct Unk_FFF01728 {
    u8 pad00[0x14];
    u32 *unk14;
};

struct Unk_FFF016F0 {
    u8 pad00[0x20];
    u32 unk20;
    u32 unk24;
    s32 unk28;
    u32 unk2C;
    u8 pad30[8];
    Unk_FFF01728 unk38;
    u8 pad50[0xB4];
    u32 unk104;
};
extern Unk_FFF016F0 DAT_FFF016F0;

struct Unk_FFF000E8 {
    u8 pad00[0x2C];
    u32 unk2C;
    u8 pad30[0xC];
    u8 unk3C[16];
};
extern Unk_FFF000E8 DAT_FFF000E8;

extern "C" u32 FUN_FFFF3134(u32 x);
extern "C" void FUN_FFFF84B4(u32 addr);
extern "C" void FUN_FFFF8520();

// Reads 0x4000 bytes from card address 0x4000 to 0x080F9000 (to the address at 0xFFF00114 when arg is nonzero) in
// 4 KB blocks, taken in the order of the 2-bit fields of the byte at 0xFFF00124 that the top nibble of the word at
// 0xFFF0066C selects: FUN_FFFF84B4 sends the command for each block and FUN_FFFF8520 reads it.
void FUN_FFFF9B70(u32 arg)
{
    Unk_FFF0064C *p = &DAT_FFF0064C;
    s16 *off = &p->unk40.unk10;
    s16 *blk = &p->unk40.unk0E;
    s16 *shift = &p->unk40.unk06;
    Unk_FFF016F0 *g = &DAT_FFF016F0;
    Unk_FFF01728 *s = &g->unk38;
    s32 v;

    u32 id = DAT_FFF0064C.unk20;
    u8 *tab = DAT_FFF000E8.unk3C;
    p->unk40.unk08 = tab + (id >> 28);
    p->unk40.unk0C = 4;
    s->unk14 = &g->unk104;
    g->unk20 = 0x4000;
    if (arg == 0) {
        g->unk24 = 0x080F9000;
    } else {
        g->unk24 = DAT_FFF000E8.unk2C;
    }
    g->unk28 = 0x4000;
    g->unk2C = FUN_FFFF3134(*s->unk14);
    p->unk40.unk00 = g->unk28;
    do {
        while ((v = (*p->unk40.unk08 >> *shift) & 3) >= p->unk40.unk0C)
            *shift += 2;
        *blk = v << 12;
        *off = 0;
        s32 b = *blk;
        FUN_FFFF84B4(g->unk20 + b);
        FUN_FFFF8520();
        *shift = (*shift + 2) & 7;
    } while (g->unk28 > 0);
}
