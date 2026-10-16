#include "types.h"

// The registers are reached as integer constants held in named pointers: armcc then derives the address of the
// data register from the control register's literal (adds r2, r1, #2) instead of folding +2 into the store.
void FUN_FFFF36B4(u8 x)
{
    volatile u16 *cnt = (volatile u16 *)0x10160000;
    volatile u8 *data = (volatile u8 *)0x10160002;
    *data = x;
    while (*cnt & 0x80) {}
}
