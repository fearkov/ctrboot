#pragma arm

extern "C" void FUN_FFFF009C(void);

// The undefined instruction exception vector: a branch to its handler.
void FUN_FFFF0004(void)
{
    FUN_FFFF009C();
}
