// The two state bytes are defined here, in a section of their own that the build places at 0xFFF0014C, and they are
// two scalars: armcc then reaches both from one literal, as the dump does, while still loading them as scalars among
// a call's arguments. A u8[2] or a struct of two u8, defined or extern, loads the second byte before a.
#include "types.h"

struct Unk_FFF000C0
{
    u8 pad00[0x34];
    u32 unk34;
};

extern u8 DAT_FFF0009C;
extern u32 DAT_FFF000AC;
extern u32 DAT_FFF000B4;
extern u32 DAT_FFF000B8;
extern Unk_FFF000C0 *DAT_FFF000C0;

// The last status (FUN_FFFF4EE8's first flag) of units 0 and 1, at 0xFFF0014C and 0xFFF0014D.
#pragma arm section rwdata = "data.FFF0014C"
static u8 sPresent0;
static u8 sPresent1;
#pragma arm section

extern "C" u32 FUN_FFFF20FC(u32 bit);
extern "C" u32 FUN_FFFF1EAC(u32 bit);
extern "C" u32 FUN_FFFF06EC();
extern "C" void FUN_FFFF0700(u32 state);
extern "C" bool FUN_FFFF4B18(u32 unit, u32 type);
extern "C" void FUN_FFFF4EE8(u32 unit, u32 mode, u8 *a, u8 *b, u8 *c);
extern "C" void FUN_FFFF5AD2(u32 unit, u32 was, u32 now, u32 a, u32 b);
extern "C" bool FUN_FFFF4B00(u32 unit);
extern "C" bool FUN_FFFF4B72(u32 unit);
extern "C" bool FUN_FFFF4AE8(u32 unit);
extern "C" bool FUN_FFFF4B5A(u32 unit);
extern "C" bool FUN_FFFF4C8C(u32 unit);
extern "C" void FUN_FFFF48B4(u32 unit);
extern "C" void FUN_FFFF489E(u32 unit);
extern "C" bool FUN_FFFF4AC0(u32 unit, u32 mask);
extern "C" bool FUN_FFFF4B8A(u32 unit, u32 mask);
extern "C" bool FUN_FFFF4AD4(u32 unit, u32 mask);
extern "C" bool FUN_FFFF4B46(u32 unit, u32 mask);
extern "C" bool FUN_FFFF4C7C(u32 unit, u32 mask);
extern "C" void FUN_FFFF4818(u32 bank, u16 value);
extern "C" u16 FUN_FFFF4820(u32 bank, u16 value);
extern "C" void FUN_FFFF4828(u32 bank, u16 value);
extern "C" void FUN_FFFF4806(u32 unit);
extern "C" bool FUN_FFFF4B9C(u32 unit);
extern "C" void FUN_FFFF2D6C();
extern "C" void FUN_FFFF2DC4();
extern "C" void FUN_FFFF2F48();
extern "C" void FUN_FFFF2F94(u32 flags);
extern "C" void FUN_FFFF2FEC();
extern "C" void FUN_FFFF303C();
extern "C" void FUN_FFFF510C();

// Services the controller's interrupts until none is pending.
void FUN_FFFF57F4()
{
    u8 a, b, c;
    if (FUN_FFFF20FC(0x10))
    {
        FUN_FFFF1EAC(0x10);
    }
    u32 state = FUN_FFFF06EC();
    do
    {
        if (FUN_FFFF4B18(DAT_FFF000B8, 0))
        {
            FUN_FFFF4EE8(DAT_FFF000B8, 0, &a, &b, &c);
            FUN_FFFF5AD2(0x200, sPresent0, a, b, c);
            sPresent0 = a;
        }
        if (FUN_FFFF4B18(DAT_FFF000B8, 1))
        {
            FUN_FFFF4EE8(DAT_FFF000B8, 1, &a, &b, &c);
            FUN_FFFF5AD2(0x201, sPresent1, a, b, c);
            sPresent1 = a;
        }
        if (FUN_FFFF4B00(DAT_FFF000B8) && FUN_FFFF4B72(DAT_FFF000B8))
        {
            if (FUN_FFFF4C8C(DAT_FFF000B8) && DAT_FFF000B4 && DAT_FFF000AC)
            {
                FUN_FFFF2F48();
            }
            else
            {
                FUN_FFFF48B4(DAT_FFF000B8);
            }
        }
        if (FUN_FFFF4AE8(DAT_FFF000B8) && FUN_FFFF4B5A(DAT_FFF000B8))
        {
            if (FUN_FFFF4C8C(DAT_FFF000B8) && DAT_FFF000B4 && DAT_FFF000AC)
            {
                FUN_FFFF303C();
            }
            else
            {
                FUN_FFFF489E(DAT_FFF000B8);
            }
        }
        if (FUN_FFFF4AC0(DAT_FFF000B8, 0x100) && FUN_FFFF4B8A(DAT_FFF000B8, 0x100))
        {
            FUN_FFFF4818(DAT_FFF000B8, 0x100);
            if (!FUN_FFFF4C8C(DAT_FFF000B8) && DAT_FFF000B4 && DAT_FFF000AC)
            {
                FUN_FFFF2DC4();
            }
        }
        if (FUN_FFFF4AC0(DAT_FFF000B8, 0x200) && FUN_FFFF4B8A(DAT_FFF000B8, 0x200))
        {
            FUN_FFFF4818(DAT_FFF000B8, 0x200);
            if (!FUN_FFFF4C8C(DAT_FFF000B8) && DAT_FFF000B4 && DAT_FFF000AC)
            {
                FUN_FFFF2FEC();
            }
        }
        if (FUN_FFFF4AD4(DAT_FFF000B8, 0x807F))
        {
            FUN_FFFF2F94(FUN_FFFF4820(DAT_FFF000B8, 0x807F));
        }
        if (DAT_FFF000C0->unk34 && DAT_FFF0009C)
        {
            FUN_FFFF2D6C();
            DAT_FFF0009C = 0;
        }
        if (FUN_FFFF4B46(DAT_FFF000B8, 4) && FUN_FFFF4C7C(DAT_FFF000B8, 4))
        {
            if (DAT_FFF0009C)
            {
                if (!DAT_FFF000B4 || !DAT_FFF000AC)
                {
                    FUN_FFFF4828(DAT_FFF000B8, 4);
                    FUN_FFFF510C();
                    FUN_FFFF4806(DAT_FFF000B8);
                    FUN_FFFF2D6C();
                    DAT_FFF0009C = 0;
                }
            }
            else
            {
                FUN_FFFF4828(DAT_FFF000B8, 4);
            }
        }
    } while (FUN_FFFF4B9C(DAT_FFF000B8));
    FUN_FFFF0700(state);
}
