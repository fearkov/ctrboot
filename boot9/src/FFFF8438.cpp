#include "types.h"

struct Unk_FFFF8438
{
    u32 p[18];
};

extern "C" u32 FUN_FFFF8470(Unk_FFFF8438 *ctx, u32 x);

// Blowfish encryption of the block (*xl, *xr); FUN_FFFF8470 is the F function.
void FUN_FFFF8438(Unk_FFFF8438 *ctx, u32 *xl, u32 *xr)
{
    u32 l = *xl;
    u32 r = *xr;
    for (int i = 0; i < 16; i++)
    {
        l ^= ctx->p[i];
        r ^= FUN_FFFF8470(ctx, l);
        u32 t = l;
        l = r;
        r = t;
    }
    u32 t = l;
    l = r;
    r = t;
    r ^= ctx->p[16];
    l ^= ctx->p[17];
    *xl = l;
    *xr = r;
}
