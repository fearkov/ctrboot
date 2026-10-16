#include "types.h"

struct Unk_FFF000C0
{
    u8 pad00[1];
    u8 unk01;
    u8 pad02[0x36];
    u32 unk38;
};

extern Unk_FFF000C0 *DAT_FFF000C0;
extern u32 DAT_FFF000B8;

extern "C" void FUN_FFFF49D8(u32 a, u32 b, u32 *c);
extern "C" void FUN_FFFF5CAC(u32 bits);

void FUN_FFFF510C()
{
    FUN_FFFF49D8(DAT_FFF000B8, 0, &DAT_FFF000C0->unk38);
    if (DAT_FFF000C0->unk38 & 0x400000) {
        FUN_FFFF5CAC(0x100);
    }
    Unk_FFF000C0 *p = DAT_FFF000C0;
    u32 v = p->unk38;
    u32 f = p->unk01;
    u32 mask;
    if (((v >> 9) & 0xF) == 5) {
        if (f != 0) {
            mask = 0x7DBF0080;
        } else {
            mask = 0x7DB90008;
        }
    } else {
        if (f != 0) {
            mask = 0xFDBF0080;
        } else {
            mask = 0xFDB90008;
        }
    }
    if (v & mask) {
        FUN_FFFF5CAC(0x80);
    }
}
