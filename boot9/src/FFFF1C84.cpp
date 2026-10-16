#include "types.h"

struct Unk_FFF01910 {
    u32 unk0;
    u32 unk4;
    u32 unk8;
    u32 unkC;
};

extern Unk_FFF01910 DAT_FFF01910[];

void FUN_FFFF1C84(u32 index, u32 value)
{
    DAT_FFF01910[index].unk8 = value;
}
