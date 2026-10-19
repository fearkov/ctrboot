#include "types.h"

extern u32 DAT_1FFE8040;

extern "C" s32 FUN_000122BC(u32* out);

// Receives a PXI message of the given type into buffer: the first word is the header, the type in bits 0-4 and the
// number of words that follow from bit 6 up. Returns -1 when the type is another one or the words do not fit in
// size bytes, 0 when they were all read.
s32 FUN_00012E58(u32 type, u32* buffer, s32 size)
{
    // a local copy of the buffer pointer gives the dump's order of the argument copies at entry
    u32* dst = buffer;
    while (FUN_000122BC(&DAT_1FFE8040) != 0) {
    }
    u32 header = DAT_1FFE8040;
    s32 result = -1;
    if ((header & 0x1F) == type) {
        s32 count = header >> 6;
        if (count <= size / 4) {
            for (s32 i = 0; i < count; i++) {
                while (FUN_000122BC(&dst[i]) != 0) {
                }
            }
            result = 0;
        }
    }
    return result;
}
