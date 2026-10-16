#include "types.h"

struct Unk_FFFF8470
{
    u32 p[18];
    u32 s[4][256];
};

// Blowfish round function.
u32 FUN_FFFF8470(Unk_FFFF8470 *ctx, u32 x)
{
    u8 d = (u8)x;
    x >>= 8;
    u8 c = (u8)x;
    x >>= 8;
    u8 b = (u8)x;
    x >>= 8;
    u8 a = (u8)x;
    u32 y = ctx->s[0][a] + ctx->s[1][b];
    y ^= ctx->s[2][c];
    return y + ctx->s[3][d];
}
