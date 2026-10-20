#pragma arm
#include "types.h"

// Sets up the MMU: invalidates the TLBs, points both translation table bases at the first-level table l1, gives every
// domain client access and enables the VFP coprocessors. Then fills l1 and the l2 area with no-access entries and maps
// 0x10000000-0x11000000 with supersections, 0x17E00000 and 0x18000000-0x18600000 with sections, and
// 0x1FF00000-0x20000000 and 0x00000000-0x00020000 through the coarse page tables at l2 and l2 + 0x100.
void FUN_000191CC(u32 *l1, u32 *l1End, u32 *l2, u32 *l2End)
{
    register u32 invalidateITlb __asm("cp15:0:c8:c5:0");
    register u32 invalidateDTlb __asm("cp15:0:c8:c6:0");
    register u32 ttbr0 __asm("cp15:0:c2:c0:0");
    register u32 ttbr1 __asm("cp15:0:c2:c0:1");
    register u32 ttbcr __asm("cp15:0:c2:c0:2");
    register u32 dacr __asm("cp15:0:c3:c0:0");
    register u32 cpacr __asm("cp15:0:c1:c0:2");
    u32 *p;
    u32 addr = 0;

    invalidateITlb = 0;
    invalidateDTlb = 0;
    u32 ttb = ((u32)l1 & ~0x3FFFu) | 2;
    ttbr0 = ttb;
    ttbr1 = ttb;
    ttbcr = 0;
    dacr = 0x55555555;
    cpacr = 0xF00000;

    for (p = l1; p < l1End; p++)
        *p = (addr & 0xFFF00000) | 0x10012;
    for (p = l2; p < l2End; p++)
        *p = 0x403;

    for (addr = 0x10000000, p = &l1[addr >> 20]; addr < 0x11000000; addr += 0x100000)
        *p++ = (addr & 0xFF000000) | 0x50416;
    addr = 0x18000000;
    l1[0x17E] = 0x17E02412;
    for (p = &l1[addr >> 20]; addr < 0x18600000; addr += 0x100000)
        *p++ = (addr & 0xFFF00000) | 0x14416;

    addr = 0x1FF00000;
    p = &l1[addr >> 20];
    *p = ((u32)l2 & ~0x3FFu) | 1;
    for (p = l2; addr < 0x1FFF0000; addr += 0x1000)
        *p++ = (addr & 0xFFFF0000) | 0xC415;
    for (; addr < 0x1FFF4000; addr += 0x1000)
        *p++ = (addr & 0xFFFFF000) | 0x517;
    for (; addr < 0x1FFFA000; addr += 0x1000)
        *p++ = (addr & 0xFFFFF000) | 0x513;
    for (; addr < 0x20000000; addr += 0x1000)
        *p++ = (addr & 0xFFFFF000) | 0x512;

    p = l2 + 0x100;
    addr = 0;
    l1[addr >> 20] = ((u32)p & ~0x3FFu) | 1;
    do {
        *p++ = (addr & 0xFFFF0000) | 0x4415;
        addr += 0x1000;
    } while (addr != 0x20000);
}
