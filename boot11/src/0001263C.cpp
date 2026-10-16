// Built for space: only -Ospace gives this code.
#pragma Ospace
#include "types.h"

struct Unk_1FFE8020 {
    u32 unk0;
    u32 unk4;
};

extern "C" void FUN_000127C8();
extern "C" void FUN_0001267C();
extern "C" void FUN_00012738();
extern "C" void FUN_00012334();
extern "C" void FUN_00013B04();
extern "C" void FUN_00011E04();
extern "C" void FUN_00018B9C();
extern Unk_1FFE8020 DAT_1FFE8020;
extern volatile u8 DAT_10141220;

void FUN_0001263C()
{
    if (DAT_1FFE8020.unk4 == 0) {
        DAT_1FFE8020.unk4 = 1;
        FUN_000127C8();
        FUN_0001267C();
        FUN_00012738();
        FUN_00012334();
        FUN_00013B04();
        FUN_00011E04();
        DAT_10141220 |= 2;
        FUN_00018B9C();
    }
}
