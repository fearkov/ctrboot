#include "types.h"

struct Unk_FFFF30B8 {
    u32 unk00;
    u32 unk04;
    u32 unk08;
    u32 unk0C;
};

void FUN_FFFF30B8(Unk_FFFF30B8 *out, u32 a, u32 b, u32 c, u32 x, u32 y, u32 e, u32 f, u32 g, u32 h)
{
    out->unk08 = (x & 0x1FFF) | ((y & 0x3F) << 16);
    out->unk00 = a | b | c | (x & 0x1FFF) | ((y & 0x3F) << 16)
               | ((e || f) ? 0x4000 : 0)
               | (g ? 0x400000 : 0)
               | (h ? 0x2000 : 0)
               | 0xA0000000;
    out->unk0C = (e || f) ? 0x4000 : g ? 0x400000 : h ? 0x2000 : 0;
}
