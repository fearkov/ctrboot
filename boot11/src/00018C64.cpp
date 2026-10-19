#include "types.h"

struct Unk_1FFE8048 {
    u32 unk0;
    u32 unk4;
    u32 unk8;
    u32 unkC;
};

extern Unk_1FFE8048 DAT_1FFE8048;

void FUN_00018C64(u32 value)
{
    DAT_1FFE8048.unkC = value;
}
