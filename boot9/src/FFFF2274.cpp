#include "types.h"

// Header word sent before a message: command, a flag kept as it was, and the length in words.
struct Unk_FFF0006C {
    u32 command : 5;
    u32 unk5 : 1;
    u32 count : 26;
};

extern Unk_FFF0006C DAT_FFF0006C;
extern "C" s32 FUN_FFFF1A44(u32 value);

void FUN_FFFF2274(u32 command, const void *data, s32 size)
{
    const u32 *words = (const u32 *)data;
    s32 count = size / 4;
    DAT_FFF0006C.command = command;
    DAT_FFF0006C.count = count;
    while (FUN_FFFF1A44(*(u32 *)&DAT_FFF0006C) != 0) {
    }
    for (s32 i = 0; i < count; i++) {
        while (FUN_FFFF1A44(words[i]) != 0) {
        }
    }
}
