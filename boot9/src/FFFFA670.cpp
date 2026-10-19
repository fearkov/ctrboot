#include "types.h"

struct Unk_FFF000E8 {
    u8 pad00[0x20];
    u32 unk20;
};
extern Unk_FFF000E8 DAT_FFF000E8;
extern u32 DAT_FFF00628;
extern u8 DAT_FFF01728[];

extern "C" u32 FUN_FFFF34BC(u8 *cmd);

// Unless 0xFFF00108 is set, sends the eight-byte command 0x90 (top byte), its response going to +0x68, and
// returns the word read back; otherwise returns the one kept at 0xFFF00628.
u32 FUN_FFFFA670()
{
    u32 *id = &DAT_FFF00628;
    if (DAT_FFF000E8.unk20 == 0) {
        u8 *cmd = DAT_FFF01728;
        *(u8 **)(cmd + 0x14) = cmd + 0x68;
        *(__packed u64 *)cmd = 0x9000000000000000ULL;
        return FUN_FFFF34BC(cmd);
    }
    return *id;
}
