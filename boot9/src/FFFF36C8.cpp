#include "types.h"

extern volatile u16 DAT_10160000;

void FUN_FFFF36C8()
{
    while (DAT_10160000 & 0x80) {}
}
