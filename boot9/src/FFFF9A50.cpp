#include "types.h"

struct Unk_FFF00628 {
    s32 unk00;
    s32 unk04;
};

extern Unk_FFF00628 DAT_FFF00628;

extern "C" void FUN_FFFF9CCC();
extern "C" void FUN_FFFF99A4();
extern "C" void FUN_FFFF9C28();
extern "C" void FUN_FFFF9B70(u32 arg);

void FUN_FFFF9A50(u32 arg)
{
    Unk_FFF00628 *state = &DAT_FFF00628;
    FUN_FFFF9CCC();
    FUN_FFFF99A4();
    FUN_FFFF9C28();
    if (state->unk00 == state->unk04) {
        FUN_FFFF9B70(arg);
    }
}
