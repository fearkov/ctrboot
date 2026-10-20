#include "types.h"

// The key of the DS cartridge Blowfish cipher: the P-array, then the S-boxes.
struct Unk_FFF006A0 {
    u32 unk000[18];
    u32 unk048[4][256];
};

struct Unk_10010000 {
    u8 pad00[0x10];
    u8 unk10;
};

extern Unk_10010000 DAT_10010000;
extern Unk_FFF006A0 DAT_FFF006A0;
extern u8 DAT_1FFFD000[0x1000];

extern "C" void FUN_FFFF03F0(const void *src, void *dst, u32 size);
extern "C" void *FUN_FFFF25F0(void *dst, const void *src, u32 size);

// The multiplier (0x5D588B656C078965) and the increment (0x269EC3) of the 64-bit generator, as little-endian bytes.
// armcc stores the increment's literal as the tail of the multiplier's, so each constant takes exactly 8 bytes.
#define LCG_MUL "\x65\x89\x07\x6C\x65\x8B\x58\x5D\xC3\x9E\x26\0\0\0\0"
#define LCG_ADD "\xC3\x9E\x26\0\0\0\0"

// Sets up the Blowfish key: when the byte at 0x10010010 is 0, from the table at 0x1FFFD000 (the P-array picked out
// of it byte by byte, the S-boxes copied); otherwise from a 64-bit linear congruential generator seeded with
// "BLOWFISH", the high word of each step giving the next word of the key.
void FUN_FFFF98E8()
{
    Unk_FFF006A0 *key = &DAT_FFF006A0;
    u8 *src = DAT_1FFFD000;
    if (DAT_10010000.unk10 == 0) {
        u8 *p = (u8 *)key->unk000;
        for (int i = 0; i < sizeof(key->unk000); i++)
            p[i] = src[(i % 16) * 256 + src[i]];
        u32 *sbox = key->unk048[0];
        FUN_FFFF03F0(src, sbox, sizeof(key->unk048));
    } else {
        u32 *out = (u32 *)key;
        u64 add;
        u64 mul;
        u64 state;
        u64 seed;
        FUN_FFFF25F0(&seed, "BLOWFISH", 8);
        FUN_FFFF25F0(&state, &seed, 8);
        FUN_FFFF25F0(&mul, LCG_MUL, 8);
        FUN_FFFF25F0(&add, LCG_ADD, 8);
        for (int i = 0; i < sizeof(*key) / 4; i++) {
            state = mul * state + add;
            out[i] = state >> 32;
        }
    }
}
