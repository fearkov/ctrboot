#include "types.h"

extern "C" u32 FUN_000121EC();
extern "C" u32 FUN_00012564();
extern "C" void FUN_0001282C(u32 state);
extern "C" void FUN_00018434(u32 bit, u32 value);
extern "C" void FUN_00018450(u32 bit, u32 value);

void FUN_00018B34(u32 value)
{
    if (FUN_000121EC() == 0) {
        u32 state = FUN_00012564();
        FUN_00018450(7, 1);
        FUN_00018434(7, value);
        FUN_0001282C(state);
    }
}
