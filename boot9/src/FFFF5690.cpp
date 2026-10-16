#include "types.h"

struct Unk_FFF000C0 {
    u8 unk00;
    u8 unk01;
    u8 pad02[0x32];
    u32 unk34;
    u32 unk38;
};

extern "C" Unk_FFF000C0 *FUN_FFFF3D78(u32 id);

// The error flags of the device with this id, and the error bits of its last status (which bits count depends on
// the kind of card in unk01). Without such a device: error 1 << 24 and no status.
void FUN_FFFF5690(u32 id, u32 *error, u32 *status)
{
    Unk_FFF000C0 *ctx = FUN_FFFF3D78(id);
    u32 value;
    if (ctx == 0) {
        *error = 0x1000000;
        value = 0;
    } else {
        u32 mask;
        *error = ctx->unk34;
        if (ctx->unk01 != 0) {
            mask = 0xFDFF0080;
        } else {
            mask = 0xFDF90008;
        }
        value = ctx->unk38 & mask;
    }
    *status = value;
}
