#include "types.h"

extern "C" void FUN_FFFF0258(void);
extern "C" void FUN_FFFF03F0(const void *src, void *dst, u32 size);

// Copies the code of FUN_FFFF0258 (0x100 bytes) to 0x07FFB700 and runs it from there.
void FUN_FFFF1748(void)
{
    FUN_FFFF03F0((const void *)FUN_FFFF0258, (void *)0x07FFB700, 0x100);
    ((void (*)(void))0x07FFB700)();
}
