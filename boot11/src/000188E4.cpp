#include "types.h"

struct Unk_1FFE8048 {
    u32 unk0;
    u32 unk4;
    u32 unk8;
    u32 unkC;
};

struct Unk_10202000 {
    u32 unk0;
    u32 unk4;
    u32 unk8;
    u32 unkC;
};

extern "C" u32 FUN_00018F20();
extern "C" void FUN_0001225C(u64 ms);
extern "C" void FUN_00018BCC(u32 value);
extern "C" u32 FUN_00018E84(s32 index, u32 color);
extern "C" bool FUN_000186AC(u32 on);
extern "C" bool FUN_00013ACA(u32 flag);
extern Unk_1FFE8048 DAT_1FFE8048;
extern volatile Unk_10202000 DAT_10202000;

// Unless FUN_00018F20 returns 1 to 5, sets 0x1FFE8054 to 4 and sets the LCD registers up, waiting 20 ms and then
// 10 ms. Returns 0 when it returned 2 or 3, otherwise 1.
u32 FUN_000188E4()
{
    switch (FUN_00018F20()) {
    case 1:
    case 4:
    case 5:
        break;
    case 2:
    case 3:
        return 0;
    default:
        DAT_1FFE8048.unkC = 4;
        FUN_0001225C(20);
        FUN_00018BCC(1);
        FUN_00018E84(0, 0xFF);
        FUN_00018E84(1, 0xFF);
        DAT_10202000.unkC &= 0xFFFEFFFE;
        FUN_0001225C(10);
        FUN_000186AC(0);
        FUN_00013ACA(1);
        break;
    }
    return 1;
}
