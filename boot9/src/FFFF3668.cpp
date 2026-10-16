#include "types.h"

extern volatile u8 DAT_10160002;

extern "C" void FUN_FFFF36C8();
extern "C" void FUN_FFFF3698(u32 x);
extern "C" void FUN_FFFF36B4(u8 x);

void FUN_FFFF3668(u8 *out)
{
    FUN_FFFF36C8();
    u8 *dst = out;
    FUN_FFFF3698(1);
    FUN_FFFF36B4(5);
    FUN_FFFF3698(0);
    DAT_10160002 = 0;
    FUN_FFFF36C8();
    *dst = DAT_10160002;
}
