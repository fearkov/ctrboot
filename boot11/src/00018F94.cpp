#include "types.h"

struct Unk_1FFE8048 {
    u32 unk0;
    u32 unk4;
    u32 unk8;
    u32 unkC;
};

struct Unk_10202000 {
    u32 unk0;
    u32 unk4;
};

extern "C" void FUN_00018FC8();
extern "C" void FUN_00018B9C();
extern "C" void FUN_0001846C();
extern Unk_1FFE8048 DAT_1FFE8048;
extern volatile Unk_10202000 DAT_10202000;

void FUN_00018F94()
{
    if (DAT_1FFE8048.unk8 == 0) {
        FUN_00018FC8();
        DAT_10202000.unk0 = 0;
        DAT_10202000.unk4 = 0x0A390A39;
        FUN_00018B9C();
        FUN_0001846C();
        DAT_1FFE8048.unkC = 0;
        DAT_1FFE8048.unk8 = 1;
    }
}
