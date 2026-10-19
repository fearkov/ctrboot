#include "types.h"

// One of the four key slots of the AES engine: normal key, X and Y, four words each.
struct Unk_10009040
{
    u32 unk00[4];
    u32 unk10[4];
    u32 unk20[4];
};

struct Unk_10009000
{
    u32 unk00;
    u8 pad04[0x0D];
    u8 unk11;
    u8 pad12[0x2E];
    Unk_10009040 unk40[4];
};

struct Unk_10009100
{
    u32 unk00;
    u32 unk04;
    u32 unk08;
};

// Sets the word and byte order in AES_CNT, then loads the X key of a slot 0-3 from data (in reverse word order
// when bit 2 of mode is set), or feeds a key through the key FIFO into slot 4-0x3F.
void FUN_FFFF8B18(u32 slot, u32 mode, const u32 *data)
{
    volatile Unk_10009000 *aes = (volatile Unk_10009000 *)0x10009000;
    aes->unk00 = (aes->unk00 & ~0x02800000) | (mode << 23);
    if (slot <= 3) {
        volatile Unk_10009040 *keys = ((volatile Unk_10009000 *)0x10009000)->unk40;
        volatile Unk_10009040 *key = keys + slot;
        if (mode & 4) {
            key->unk10[0] = data[3];
            key->unk10[1] = data[2];
            key->unk10[2] = data[1];
            key->unk10[3] = data[0];
        } else {
            key->unk10[0] = data[0];
            key->unk10[1] = data[1];
            key->unk10[2] = data[2];
            key->unk10[3] = data[3];
        }
    } else if (slot - 4 <= 0x3B) {
        aes->unk11 = (aes->unk11 & ~0x3F) | slot | 0x80;
        ((volatile Unk_10009100 *)0x10009100)->unk04 = data[0];
        ((volatile Unk_10009100 *)0x10009100)->unk04 = data[1];
        ((volatile Unk_10009100 *)0x10009100)->unk04 = data[2];
        ((volatile Unk_10009100 *)0x10009100)->unk04 = data[3];
    }
}
