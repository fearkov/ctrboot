#include "types.h"

extern "C" void FUN_FFFF1D94(u32 handle);
extern "C" void FUN_FFFF89E4();
extern "C" void FUN_FFFFAE3C();
extern u32 DAT_FFF00150;
extern u32 DAT_FFF00154;
extern u32 DAT_FFF00158;

void FUN_FFFF3F70()
{
    FUN_FFFF1D94(DAT_FFF00150);
    FUN_FFFF89E4();
    FUN_FFFF1D94(DAT_FFF00154);
    FUN_FFFFAE3C();
    FUN_FFFF1D94(DAT_FFF00158);
}
