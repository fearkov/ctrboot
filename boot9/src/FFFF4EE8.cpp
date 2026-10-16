#include "types.h"

extern "C" u16 FUN_FFFF4830(u32 unit, u16 mask);
extern "C" u16 FUN_FFFF4FB8(u32 unit, u32 offset, u16 mask);

void FUN_FFFF4EE8(u32 unit, u32 mode, u8 *a, u8 *b, u8 *c)
{
    u32 st;
    switch (mode) {
    case 0:
        st = FUN_FFFF4830(unit, 0x18);
        if (a != 0) {
            if (st & 0x20) {
                *a = 1;
            } else {
                *a = 0;
            }
        }
        if (b != 0) {
            if (st & 0x10) {
                *b = 1;
            } else {
                *b = 0;
            }
        }
        if (c != 0) {
            if (st & 0x08) {
                *c = 1;
            } else {
                *c = 0;
            }
        }
        break;
    case 1:
        st = FUN_FFFF4FB8(unit, 0xF8, 3);
        if (a != 0) {
            if (st & 4) {
                *a = 1;
            } else {
                *a = 0;
            }
        }
        if (b != 0) {
            if (st & 2) {
                *b = 1;
            } else {
                *b = 0;
            }
        }
        if (c != 0) {
            if (st & 1) {
                *c = 1;
            } else {
                *c = 0;
            }
        }
        break;
    }
}
