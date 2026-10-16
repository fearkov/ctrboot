#include "types.h"

extern volatile u32 DAT_1000B000;

u32 FUN_FFFFA874()
{
    return DAT_1000B000 & 1;
}
