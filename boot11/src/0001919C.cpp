#include "types.h"

extern "C" void FUN_0001867C(u32* a, u32* b, u32* c);
extern "C" void FUN_00018C70(u32 which, u32 arg, u32 value);

void FUN_0001919C(u32 flags, u32 arg)
{
    if (flags & 1) {
        u32 value;
        FUN_0001867C(&value, 0, 0);
        FUN_00018C70(1, arg, value);
    }
    if (flags & 2)
        FUN_00018C70(2, arg, 0);
}
