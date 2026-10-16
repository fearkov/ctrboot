#include "types.h"

struct Unk_10009000
{
    u32 unk00;
    u8 pad04[0xc];
    u8 unk10;
};

extern volatile Unk_10009000 DAT_10009000;

// Selects an AES key slot (AES_KEYSEL at 0x10009010) and sets AES_CNT bit 26 to apply it.
void FUN_FFFF898C(u32 slot)
{
    if (slot <= 0x3f)
    {
        volatile Unk_10009000 *aes = &DAT_10009000;
        u32 cnt = aes->unk00;
        aes->unk10 = slot;
        aes->unk00 = cnt | 0x4000000;
    }
}
