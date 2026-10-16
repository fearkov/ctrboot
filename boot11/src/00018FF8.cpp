#include "types.h"

extern "C" void FUN_00018A10(u32 a, u32 b, u32 c, u32 d, u32 e);
extern "C" void FUN_00018950(u32 a, u32 b, u32 c, u32 d, void (*callback)(u32, u32, u32, u32, u32), u32 e, u32 f);

void FUN_00018FF8(u32 a, u32 b, u32 c, u32 d)
{
    FUN_00018950(a, b, c, d, FUN_00018A10, 3, 5);
}
