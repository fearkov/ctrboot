#pragma arm
#include "types.h"

void FUN_FFFF0198(u32 count)
{
    do {
        count -= 4;
    } while (count < 0xFFFFFFFCu);
}
