#include "types.h"

extern "C" void FUN_000115B4();
extern "C" void FUN_00011730(const void* src, void* dst, u32 size);

void FUN_000120E0()
{
    u32 code[0x40];
    FUN_00011730((const void*)FUN_000115B4, code, sizeof(code));
    ((void (*)())code)();
}
