#include "types.h"

typedef void (*Unk_Callback)();

// Thumb entries (bit 0 set) of the callbacks, which boot9.functions does not list.
extern u8 DAT_FFFFA15D;
extern u8 DAT_FFFFA21B;
extern u8 DAT_FFFFA319;
extern u8 DAT_FFFFA3E7;

extern "C" void FUN_FFFFADF4(u32 a, u32 b, u32 c, u32 d, u32 e, u32 f, u32 g, u32 h);
extern "C" void FUN_FFFF8FC0(u32 mode, Unk_Callback a, Unk_Callback b, Unk_Callback c, Unk_Callback d);

void FUN_FFFF8F60()
{
    FUN_FFFFADF4(3, 7, 3, 7, 3, 7, 3, 7);
    FUN_FFFF8FC0(0, (Unk_Callback)&DAT_FFFFA3E7, (Unk_Callback)&DAT_FFFFA21B, (Unk_Callback)&DAT_FFFFA319,
                 (Unk_Callback)&DAT_FFFFA15D);
}
