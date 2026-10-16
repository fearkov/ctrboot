#include "types.h"

extern u32 DAT_0800003C;

u32 FUN_FFFF20FC(u32 bit)
{
    return (DAT_0800003C >> bit) & 1;
}
