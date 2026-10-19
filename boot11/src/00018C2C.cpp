#include "types.h"

extern "C" u32 FUN_00012564();
extern "C" void FUN_0001282C(u32 state);
extern "C" void FUN_0001222C(u32 irq, u32 priority);
extern "C" void FUN_00012870(u32 irq, u32 value);
extern "C" void FUN_00012474(u32 irq);
extern "C" u32 FUN_00012590(u32 irq);

void FUN_00018C2C(u32 n, u32 value)
{
    u32 irq = n + 0x2A;
    u8 priority = n + 5;
    u32 state = FUN_00012564();
    FUN_0001222C(irq, priority);
    FUN_00012870(irq, value);
    FUN_00012474(irq);
    FUN_00012590(irq);
    FUN_0001282C(state);
}
