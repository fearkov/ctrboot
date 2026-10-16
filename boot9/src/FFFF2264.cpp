#include "types.h"

extern volatile u32 DAT_10008000;

u8 FUN_FFFF2264()
{
    return (u8)DAT_10008000;
}
