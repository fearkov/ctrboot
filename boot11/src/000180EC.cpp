// Built at -O0 (#pragma O0, below the helpers): the dump builds the auxiliary control bits in r1 ("mov r1, #0x2f /
// orr r0, r0, r1"), which armcc folds into "orr r0, r0, #0x2f" at every other level. The CP15 reads and that mask go
// through small inline helpers defined above the pragma, so they are compiled at -O3: at -O0 armcc keeps the value a
// helper returns in a register instead of folding it, and it orrs in place into the register the helper read CP15
// into (a CP15 register variable read in the -O0 function itself stays live, so the result goes to r2), without the
// nop it puts in front of a helper compiled at -O0. The SCU address is in r3 while r0 is free, which armcc only does
// for a register variable, so it is a global register variable on r3.
#pragma arm
#include "types.h"

extern volatile u32 DAT_17E00000;

register volatile u32 *gScu __asm("r3");

static inline u32 read_control()
{
    register u32 control __asm("cp15:0:c1:c0:0");
    return control;
}

static inline u32 read_aux_control()
{
    register u32 aux_control __asm("cp15:0:c1:c0:1");
    return aux_control;
}

static inline u32 in_register(u32 value)
{
    return value;
}

#pragma O0

// Turns the snoop control unit on, then the return stack, branch prediction, instruction folding and SMP mode in the
// auxiliary control register, and the MMU, the caches, branch prediction, unaligned access and the ARMv6 page table
// format in the CP15 control register; then invalidates both caches and waits for the writes to finish.
void FUN_000180EC()
{
    register u32 control __asm("cp15:0:c1:c0:0");
    register u32 aux_control __asm("cp15:0:c1:c0:1");
    register u32 invalidate_icache __asm("cp15:0:c7:c5:0");
    register u32 invalidate_dcache __asm("cp15:0:c7:c6:0");
    register u32 drain_write_buffer __asm("cp15:0:c7:c10:4");

    gScu = &DAT_17E00000;
    *gScu |= 1;
    aux_control = read_aux_control() | in_register(0x2F);
    control = read_control() | 0xC01805;
    invalidate_icache = 0;
    invalidate_dcache = 0;
    drain_write_buffer = 0;
}
