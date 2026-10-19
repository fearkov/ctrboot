#pragma arm

extern "C" void FUN_00019390();

// Tail call into the routine that sets up the RAM data: it copies the initialized data from the ROM and clears
// the rest.
void FUN_0001813C()
{
    FUN_00019390();
}
