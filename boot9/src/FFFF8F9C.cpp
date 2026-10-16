#include "types.h"

typedef void (*Unk_Callback)();

// Thumb entries (bit 0 set) of the callbacks, which boot9.functions does not list.
extern u8 DAT_FFFFA10D;
extern u8 DAT_FFFFA1C9;
extern u8 DAT_FFFFA289;
extern u8 DAT_FFFFA3C5;

extern "C" void FUN_FFFF8FC0(u32 mode, Unk_Callback a, Unk_Callback b, Unk_Callback c, Unk_Callback d);

void FUN_FFFF8F9C()
{
    FUN_FFFF8FC0(0, (Unk_Callback)&DAT_FFFFA3C5, (Unk_Callback)&DAT_FFFFA1C9, (Unk_Callback)&DAT_FFFFA289,
                 (Unk_Callback)&DAT_FFFFA10D);
}
