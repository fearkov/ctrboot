#include "types.h"

typedef void (*Unk_Handler)();

// One handler per ARM9 interrupt.
extern Unk_Handler DAT_FFF001B4[30];

// The handlers are small Thumb functions that boot9.functions does not list yet.
extern u8 DAT_FFFF1908;
extern u8 DAT_FFFF190A;
extern u8 DAT_FFFF1914;
extern u8 DAT_FFFF191E;
extern u8 DAT_FFFF1928;
extern u8 DAT_FFFF1932;
extern u8 DAT_FFFF193C;
extern u8 DAT_FFFF1946;
extern u8 DAT_FFFF1950;
extern u8 DAT_FFFF195A;

#define THUMB_HANDLER(code) ((Unk_Handler)((u32)&(code) + 1))

void FUN_FFFF1764()
{
    for (s32 i = 0; i < 30; i++) {
        DAT_FFF001B4[i] = THUMB_HANDLER(DAT_FFFF1908);
    }
    DAT_FFF001B4[0] = THUMB_HANDLER(DAT_FFFF190A);
    DAT_FFF001B4[1] = THUMB_HANDLER(DAT_FFFF1914);
    DAT_FFF001B4[2] = THUMB_HANDLER(DAT_FFFF191E);
    DAT_FFF001B4[3] = THUMB_HANDLER(DAT_FFFF1928);
    DAT_FFF001B4[4] = THUMB_HANDLER(DAT_FFFF1932);
    DAT_FFF001B4[5] = THUMB_HANDLER(DAT_FFFF193C);
    DAT_FFF001B4[6] = THUMB_HANDLER(DAT_FFFF1946);
    DAT_FFF001B4[7] = THUMB_HANDLER(DAT_FFFF1950);
    DAT_FFF001B4[28] = THUMB_HANDLER(DAT_FFFF195A);
}
