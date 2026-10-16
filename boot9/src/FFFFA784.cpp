#include "types.h"

extern "C" u32 FUN_FFFFA73C(u8 **p, u8 *tag, u32 *len);

// Walks a DER DigestInfo, SEQUENCE { SEQUENCE { algorithm }, OCTET STRING digest }: enters the outer
// SEQUENCE, skips the inner one and stores in *end (when given) where the digest's contents start.
u32 FUN_FFFFA784(u8 *p, u8 **end)
{
    u8 tag;
    u32 len;
    if (p == 0 || !FUN_FFFFA73C(&p, &tag, &len) || tag != 0x30 || !FUN_FFFFA73C(&p, &tag, &len) || tag != 0x30) {
        return 0;
    }
    p += len;
    FUN_FFFFA73C(&p, &tag, &len);
    if (end) {
        *end = p;
    }
    return 1;
}
