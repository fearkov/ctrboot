#include "types.h"

struct Unk_FFF00280 {
    u8 unk00;
    u8 unk01;
    u8 unk02;
    u8 unk03;
    u8 pad04[0x30];
    u32 unk34;
    u8 pad38[4];
    u16 unk3C;
    u16 unk3E;
    u8 pad40[0x10];
    u32 unk50;
    u8 pad54[4];
    u32 unk58;
    u8 pad5C[8];
};

extern "C" void *FUN_FFFF056C(void *dst, u32 value, u32 size);
extern Unk_FFF00280 DAT_FFF002E4;

void FUN_FFFF5730(u32 id)
{
    Unk_FFF00280 *p;
    switch (id) {
    case 0x200:
        p = &DAT_FFF002E4 - 1;
        break;
    case 0x201:
        p = &DAT_FFF002E4;
        break;
    default:
        return;
    }
    FUN_FFFF056C(p, 0, sizeof(Unk_FFF00280));
    p->unk00 = 0;
    p->unk01 = 0;
    p->unk02 = 0;
    p->unk03 = 0;
    p->unk34 = 0;
    p->unk50 = 0;
    p->unk58 = 0;
    p->unk3C = 0x40;
    p->unk3E = 0x40EB;
}
