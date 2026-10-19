#include "types.h"

extern "C" u32 FUN_FFFF34BC(u8 *cmd);

// Sends an eight-byte card command (0xD6 in its top byte) from the start of this buffer and returns the word
// FUN_FFFF34BC reads back; 0x14 holds the pointer that FUN_FFFF34BC passes on (here the buffer's own tail, +0x90).
u32 FUN_FFFF3284(u8 *cmd)
{
    *(u8 **)(cmd + 0x14) = cmd + 0x90;
    *(__packed u64 *)cmd = 0xD600000000000000ULL;
    return FUN_FFFF34BC(cmd);
}
