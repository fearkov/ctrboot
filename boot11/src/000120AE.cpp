// The wait loop is laid out as "b test / body / test: beq body", the way armcc does it when
// building for space; with -Otime it puts the test in front of the body and jumps back.
#pragma Ospace
#include "types.h"

extern "C" u32 FUN_00012564();
extern "C" void FUN_00012590(u32 irq);
extern "C" s32 FUN_00012808(u32 irq);
extern "C" void FUN_00011A44();
extern "C" s32 FUN_00012E58(u32 id, u32* data, u32 size);

u32 FUN_000120AE()
{
    u32 value = 0;
    FUN_00012564();
    FUN_00012590(0x50);
    while (FUN_00012808(0x50) == 0)
        FUN_00011A44();
    while (FUN_00012E58(4, &value, 4) != 0) {
    }
    return value;
}
