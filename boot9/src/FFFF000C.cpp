#pragma arm

extern "C" void FUN_FFFF00A4(void);

// The prefetch abort exception vector: a branch to its handler.
void FUN_FFFF000C(void)
{
    FUN_FFFF00A4();
}
