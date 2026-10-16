#include "types.h"

extern u32 DAT_FFF00628;
extern u8 DAT_FFF01728[];

extern "C" u32 FUN_FFFF3284(u8 *cmd);
extern "C" void FUN_FFFF351C(u8 *cmd);

u32 FUN_FFFF34E0()
{
    u32 result = 0;
    u32 flags = DAT_FFF00628;
    u8 *cmd = DAT_FFF01728;
    if ((s32)(flags << 2) >= 0) {
        return 1;
    }
    if (((FUN_FFFF3284(cmd) & 0xF) >> 2) != 0) {
        FUN_FFFF351C(cmd);
        while ((s32)(FUN_FFFF3284(cmd) << 26) >= 0) {}
        result = 1;
    }
    return result;
}
