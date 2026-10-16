#include "types.h"

extern "C" u32 FUN_00012564();
extern "C" void FUN_0001282C(u32 state);
extern u8 DAT_1FFE80CA[];

void FUN_000125C8(u32 index)
{
    u32 state = FUN_00012564();
    DAT_1FFE80CA[index] |= 2;
    FUN_0001282C(state);
}
