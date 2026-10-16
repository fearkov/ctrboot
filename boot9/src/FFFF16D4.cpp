#include "types.h"

extern "C" u32 FUN_FFFF1F38(void);
extern "C" void FUN_FFFF07B0(void);
extern "C" void FUN_FFFF0830(void);
extern "C" void FUN_FFFF096C(void);
extern "C" void FUN_FFFF0A74(void);
extern "C" void FUN_FFFF0AB4(void);
extern "C" void FUN_FFFF1F00(void);
extern "C" void FUN_FFFF1EA4(void);
extern "C" void FUN_FFFF1EF8(void);
extern "C" void FUN_FFFF1E9C(void);
extern "C" void FUN_FFFF0C58(void);
extern u32 DAT_10001000;

void FUN_FFFF16D4(void)
{
    FUN_FFFF1F38();
    FUN_FFFF07B0();
    FUN_FFFF0830();
    FUN_FFFF096C();
    FUN_FFFF0A74();
    FUN_FFFF0AB4();
    FUN_FFFF1F00();
    FUN_FFFF1EA4();
    FUN_FFFF1EF8();
    FUN_FFFF1E9C();
    DAT_10001000 = 0;
    FUN_FFFF0C58();
}
