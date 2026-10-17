#include "types.h"

struct Unk_FFFF41E8
{
    u8 pad00[0xB];
    u8 rate : 2;
    u8 pad0B : 1;
    u8 mult : 4;
};

extern "C" void FUN_FFFF4E68(u32 unit, u16 value);

// Sets the card clock divider of unit from the CSD TRAN_SPEED byte: the transfer rate unit (100 kbit/s, 1, 10 or
// 100 Mbit/s) and the time value code pick the fastest divider that stays within the card's maximum rate.
void FUN_FFFF41E8(u32 unit, Unk_FFFF41E8 *csd)
{
    u32 mult = csd->mult;
    switch (csd->rate) {
    case 0:
        if (mult >= 12) {
            FUN_FFFF4E68(unit, 0x20);
        } else if (mult >= 7) {
            FUN_FFFF4E68(unit, 0x40);
        } else {
            FUN_FFFF4E68(unit, 0x80);
        }
        break;
    case 1:
        if (mult >= 10) {
            FUN_FFFF4E68(unit, 4);
        } else if (mult >= 6) {
            FUN_FFFF4E68(unit, 8);
        } else if (mult >= 2) {
            FUN_FFFF4E68(unit, 0x10);
        } else {
            FUN_FFFF4E68(unit, 0x20);
        }
        break;
    case 2:
        if (mult >= 8) {
            FUN_FFFF4E68(unit, 0);
        } else if (mult >= 5) {
            FUN_FFFF4E68(unit, 1);
        } else {
            FUN_FFFF4E68(unit, 2);
        }
        break;
    default:
        FUN_FFFF4E68(unit, 0);
        break;
    }
}
