#include "types.h"

extern "C" void FUN_FFFF1D94(u32 handle);
extern "C" void FUN_FFFF89E4();
extern "C" void FUN_FFFFAE3C();
extern "C" void FUN_FFFF1DBC(u32 handle);
extern u32 DAT_FFF00150;
extern u32 DAT_FFF00154;
extern u32 DAT_FFF0015C;

void FUN_FFFF4508()
{
    FUN_FFFF1D94(DAT_FFF00150);
    FUN_FFFF89E4();
    FUN_FFFF1D94(DAT_FFF00154);
    FUN_FFFFAE3C();
    FUN_FFFF1DBC(DAT_FFF0015C);
}
