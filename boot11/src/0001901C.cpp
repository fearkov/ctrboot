#include "types.h"

namespace std {
typedef struct __va_list {
    void* __ap;
} va_list;
}

extern "C" s32 FUN_000128F8(char* buffer, u32 size, const char* format, std::va_list args);
extern "C" void FUN_00018FF8(u32 a, u32 b, u32 c, const char* text);

s32 FUN_0001901C(u32 a, u32 b, u32 c, const char* format, ...)
{
    char buffer[0x80];
    char* text = buffer;
    std::va_list args;
    __va_start(args, format);
    s32 length = FUN_000128F8(buffer, 0x7F, format, args);
    FUN_00018FF8(a, b, c, text);
    return length;
}
