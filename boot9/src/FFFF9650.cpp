#include "types.h"

struct Unk_FFF000E8 {
    u8 pad00[0xC];
    void (*unkC)(u8 *cmd);
};
extern Unk_FFF000E8 DAT_FFF000E8;
extern u8 DAT_FFF01728[];

extern "C" void FUN_FFFF8678(u64 *block);

// Hands the command buffer to the sender whose pointer is at 0xFFF000F4. Taking the buffer's address in its own
// statement sets r0 before the sender's pointer is loaded (through r1), as in the dump; passing the caller's local
// loads the pointer through r0 and sets r0 after it.
static inline void SendCommand()
{
    u8 *cmd = DAT_FFF01728;
    DAT_FFF000E8.unkC(cmd);
}

// Builds the eight-byte card command 0xA0 (top byte) at 0xFFF01728, with its response pointer (+0x14) set to +0x40 and
// FUN_FFFF8678 filling bits 20-43, and sends it.
void FUN_FFFF9650()
{
    u8 *cmd = DAT_FFF01728;
    *(u8 **)(cmd + 0x14) = cmd + 0x40;
    *(__packed u64 *)cmd = 0xA000000000000000ULL;
    FUN_FFFF8678((u64 *)cmd);
    SendCommand();
}
