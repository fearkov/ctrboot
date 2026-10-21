#pragma arm

extern "C" void FUN_FFFF0088(void);

// The IRQ exception vector: a branch to its handler.
void FUN_FFFF0018(void)
{
    FUN_FFFF0088();
}
