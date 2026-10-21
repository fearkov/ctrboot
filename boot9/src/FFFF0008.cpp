#pragma arm

extern "C" void FUN_FFFF0094(void);

// The SVC exception vector: a branch to its handler.
void FUN_FFFF0008(void)
{
    FUN_FFFF0094();
}
