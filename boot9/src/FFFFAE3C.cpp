#include "types.h"

extern u16 DAT_FFF00240;
extern volatile u32 DAT_1000A000;

void FUN_FFFFAE3C()
{
    DAT_1000A000 = DAT_FFF00240 & ~0x504;
}
