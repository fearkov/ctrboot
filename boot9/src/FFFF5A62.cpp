#include "types.h"

struct Unk_FFFF5A62 {
    u8 pad00[0xE];
    u16 unk0E;
};

// On the CSD (as FUN_FFFF49D8 stores a long response): whether its SPEC_VERS field, bits 5:2 of the byte at 0xE, is 4
// or more.
u32 FUN_FFFF5A62(Unk_FFFF5A62 *csd)
{
    if (((csd->unk0E & 0x3F) >> 2) >= 4) {
        return 1;
    }
    return 0;
}
