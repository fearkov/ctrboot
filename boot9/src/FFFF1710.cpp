#include "types.h"

extern "C" u32 FUN_FFFF1F38(void);
extern "C" u32 FUN_FFFF8D40(void);
extern "C" u32 FUN_FFFF8D30(void);
extern "C" void FUN_FFFF2274(u32 command, const void *data, s32 size);

// The register is reached as an absolute address: armcc then builds 0x20000000 from the register that holds the
// address (one shift) instead of from a constant.
void FUN_FFFF1710(void)
{
    u32 value = 0;
    FUN_FFFF1F38();
    value = FUN_FFFF8D40();
    FUN_FFFF2274(4, &value, sizeof(value));
    *(volatile u32 *)0x10008000 |= 0x20000000;
    if (value != 0) {
        value = FUN_FFFF8D30();
    }
}
