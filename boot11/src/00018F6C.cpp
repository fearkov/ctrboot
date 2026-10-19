#include "types.h"

extern "C" void FUN_0001867C(u32 *a, u32 *b, u32 *c);
extern "C" u32 FUN_00018640(u32 which, u32 value);

u32 FUN_00018F6C(u32 flags)
{
    if (flags & 1) {
        u32 value;
        FUN_0001867C(&value, 0, 0);
        return FUN_00018640(1, value);
    }
    if (flags & 2)
        return FUN_00018640(2, 0);
    return 0x19;
}
