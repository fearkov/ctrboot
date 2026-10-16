#include "types.h"

extern "C" void FUN_00018A3C(u32 a, u32 b, u32 c, u32 d, u32 e, const u32* table, u32 f, u32 g);
extern const u32 DAT_0001817C[];

void FUN_00018A10(u32 a, u32 b, u32 c, u32 d, u32 e)
{
    FUN_00018A3C(a, b, c, d, e, DAT_0001817C, 3, 5);
}
