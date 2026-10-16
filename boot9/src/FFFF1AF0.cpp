// Built for space (armcc's default), like the other one-shot initialisers of this ROM.
#pragma Ospace
#include "types.h"

struct Unk_FFF01910 {
    u32 unk0;
    u32 unk4;
    u32 unk8;
    u32 unkC;
};

extern Unk_FFF01910 DAT_FFF01910[];

void FUN_FFFF1AF0()
{
    Unk_FFF01910 *entry = DAT_FFF01910;
    for (int i = 0; i <= 7; i++) {
        entry->unk0 = 1;
        entry->unk4 = 0;
        entry->unk8 = 0x40000;
        entry->unkC = 0xFFFFFFFF;
        entry++;
    }
}
