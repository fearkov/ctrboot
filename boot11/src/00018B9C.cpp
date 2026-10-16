#include "types.h"

struct Unk_1FFE8048 {
    u32 unk0;
    u32 unk4;
    u32 unk8;
    u32 unkC;
};

extern "C" u32 FUN_000121EC();
extern "C" u32 FUN_00012564();
extern "C" void FUN_0001282C(u32 state);
extern "C" void FUN_00018B34(u32 value);
extern "C" void FUN_00018BCC(u32 value);
extern Unk_1FFE8048 DAT_1FFE8048;

void FUN_00018B9C()
{
    if (DAT_1FFE8048.unk0 == 0) {
        u32 state = FUN_00012564();
        FUN_000121EC();
        FUN_00018BCC(0);
        FUN_00018B34(0);
        FUN_0001282C(state);
        DAT_1FFE8048.unk0 = 1;
    }
}
