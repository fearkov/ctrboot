#include "types.h"

extern "C" void FUN_00012270(u64 ns);

// Waits ms milliseconds.
void FUN_0001225C(u64 ms)
{
    FUN_00012270(ms * 1000000);
}
