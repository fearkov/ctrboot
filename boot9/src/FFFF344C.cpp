#include "types.h"

struct Unk_10164000 {
    u8 unk0[4];
    volatile u32 unk4;
    u8 unk8[0x14];
    volatile u32 unk1C;
};
extern Unk_10164000 DAT_10164000;

struct Unk_FFFF344C {
    u8 unk0[8];
    u32 unk8;
    u8 unkC[8];
    u32 *unk14;
};

extern "C" u32 FUN_FFFF46C0();
extern "C" void FUN_FFFF35C0(u32 n);
extern "C" void FUN_FFFF3570(Unk_FFFF344C *cmd);
extern "C" void FUN_FFFF355C(u32 *flags);
extern "C" void FUN_FFFF31D0(u32 channel, u32 *dst);

void FUN_FFFF344C(u32 *dst, u32 size, Unk_FFFF344C *cmd, void (*callback)(u32, u32 *))
{
    u32 n = cmd->unk8;
    if (FUN_FFFF46C0()) {
        FUN_FFFF35C0(n);
        FUN_FFFF3570(cmd);
        if (n <= 7) {
            callback(n, dst);
            FUN_FFFF355C(cmd->unk14);
        } else {
            u32 step = 0;
            if (callback == FUN_FFFF31D0) {
                step = 4;
            }
            FUN_FFFF355C(cmd->unk14);
            u32 *end = (u32 *)((u8 *)dst + size);
            u32 status;
            do {
                status = DAT_10164000.unk4;
                if (status & 0x800000) {
                    u32 word = DAT_10164000.unk1C;
                    if (dst < end) {
                        *dst = word;
                        dst = (u32 *)((u8 *)dst + step);
                    }
                }
            } while ((s32)status < 0);
        }
    }
}
