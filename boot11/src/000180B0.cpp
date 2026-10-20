// Built at -O0 (#pragma O0, below the helpers): the dump builds each mask in r1 before it uses it ("ldr r1,
// =0x32409B07 / orr r1, r1, #0x2000" and "mov r1, #0x1f / bic r0, r0, r1"), which armcc folds into one constant at
// every other level. The CP15 reads and the masks go through small inline helpers defined above the pragma, so they
// are compiled at -O3: at -O0 armcc keeps the value a helper returns in a register instead of folding it, and it
// bics in place into the register the helper read CP15 into (a CP15 register variable read in the -O0 function
// itself stays live, so the result goes to r2), without the nop it puts in front of a helper compiled at -O0.
#pragma arm
#include "types.h"

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

// Turns the MMU, the caches, branch prediction, the high vectors and the other features of the mask off in the CP15
// control register, turns the return stack, branch prediction, instruction folding and exclusive caching off in the
// auxiliary control register, invalidates both caches and waits for the writes to finish.
void FUN_000180B0()
{
    register u32 control __asm("cp15:0:c1:c0:0");
    register u32 aux_control __asm("cp15:0:c1:c0:1");
    register u32 invalidate_icache __asm("cp15:0:c7:c5:0");
    register u32 invalidate_dcache __asm("cp15:0:c7:c6:0");
    register u32 drain_write_buffer __asm("cp15:0:c7:c10:4");

    control = read_control() & ~(in_register(0x32409B07) | 0x2000);
    aux_control = read_aux_control() & ~in_register(0x1F);
    invalidate_icache = 0;
    invalidate_dcache = 0;
    drain_write_buffer = 0;
}
