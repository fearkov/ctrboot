#include "types.h"

extern "C" void *FUN_FFFF25F0(void *dst, const void *src, u32 size);

#define BSWAP32(x) (((x) >> 24) | (((x) & 0xFF0000) >> 8) | (((x) & 0xFF00) << 8) | ((x) << 24))

void FUN_FFFF86C0(u32 mode, u32 *ctr, u64 value)
{
    u64 v[2];
    u64 old;
    u32 *w = (u32 *)v;
    switch (mode) {
    case 0:
        w[0] = ctr[0];
        w[1] = ctr[1];
        w[2] = ctr[2];
        w[3] = ctr[3];
        break;
    case 1:
        w[0] = BSWAP32(ctr[0]);
        w[1] = BSWAP32(ctr[1]);
        w[2] = BSWAP32(ctr[2]);
        w[3] = BSWAP32(ctr[3]);
        break;
    case 4:
        w[0] = ctr[3];
        w[1] = ctr[2];
        w[2] = ctr[1];
        w[3] = ctr[0];
        break;
    case 5:
        w[0] = BSWAP32(ctr[3]);
        w[1] = BSWAP32(ctr[2]);
        w[2] = BSWAP32(ctr[1]);
        w[3] = BSWAP32(ctr[0]);
        break;
    }
    FUN_FFFF25F0(&old, v, 8);
    v[0] += value;
    if (v[0] < old) {
        v[1]++;
    }
    switch (mode) {
    case 0:
        ctr[0] = w[0];
        ctr[1] = w[1];
        ctr[2] = w[2];
        ctr[3] = w[3];
        break;
    case 1:
        ctr[0] = BSWAP32(w[0]);
        ctr[1] = BSWAP32(w[1]);
        ctr[2] = BSWAP32(w[2]);
        ctr[3] = BSWAP32(w[3]);
        break;
    case 4:
        ctr[3] = w[0];
        ctr[2] = w[1];
        ctr[1] = w[2];
        ctr[0] = w[3];
        break;
    case 5:
        ctr[3] = BSWAP32(w[0]);
        ctr[2] = BSWAP32(w[1]);
        ctr[1] = BSWAP32(w[2]);
        ctr[0] = BSWAP32(w[3]);
        break;
    }
}
