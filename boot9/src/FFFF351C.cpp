#include "types.h"

extern "C" void FUN_FFFF4740(u8 *cmd);

// Sends the eight-byte card command with 0xB5 in its top byte from the start of this buffer; 0x14 holds the pointer
// FUN_FFFF4740 passes on (the buffer's own tail, +0x54).
void FUN_FFFF351C(u8 *cmd)
{
    *(u8 **)(cmd + 0x14) = cmd + 0x54;
    *(__packed u64 *)cmd = 0xB500000000000000ULL;
    FUN_FFFF4740(cmd);
}
