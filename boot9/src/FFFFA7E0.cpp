// Built for space like the other loops of this ROM: the loop test sits at the bottom and is entered by a branch.
#pragma Ospace
#include "types.h"

u8 *FUN_FFFFA7E0(u8 *p, s32 len)
{
    if (*p++ != 0) {
        return 0;
    }
    u8 type = *p++;
    if (type != 1 && type != 2) {
        return 0;
    }
    len -= 2;
    while (*p != 0) {
        if (type == 1 && *p != 0xff) {
            return 0;
        }
        p++;
        if (--len < 1) {
            return 0;
        }
    }
    return p + 1;
}
