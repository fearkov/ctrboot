#include "types.h"

// Reads a DER tag and its length from *pp (short form, or long form with up to four length bytes) and
// advances *pp to the contents.
u32 FUN_FFFFA73C(u8 **pp, u8 *tag, u32 *length)
{
    if (pp == 0) {
        return 0;
    }
    u8 *p = *pp;
    u8 t = p[0];
    // reused as the count of length bytes in the long form: a counter of its own gets the registers of
    // the pointer and the counter swapped
    u8 l = p[1];
    p += 2;
    u32 len;
    if (l & 0x80) {
        l &= 0x7F;
        if (l > 4) {
            return 0;
        }
        len = 0;
        while (l--) {
            len = (len << 8) | *p++;
        }
    } else {
        len = l;
    }
    if (tag) {
        *tag = t;
    }
    if (length) {
        *length = len;
    }
    *pp = p;
    return 1;
}
