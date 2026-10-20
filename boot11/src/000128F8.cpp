// The number being printed is copied in whole with memcpy where the dump does so: the starting zero from an
// eight-byte literal (an explicit call, which sets up its arguments in the dump's order), and a 64-bit argument and
// each quotient of a 64-bit division by ten through a __packed pointer, which armcc stores with memcpy.
#include "types.h"

namespace std {
typedef struct __va_list {
    void* __ap;
} va_list;
}

// Where the text goes: the room left (the terminating NUL not counted), the write position, which keeps moving
// past the end so that it counts the whole length, and the start of the buffer.
struct Unk_000128F8 {
    u32 len;
    char* cur;
    char* base;
};

// The conversion's flags.
enum {
    FLAG_SPACE = 0x1, // ' '
    FLAG_PLUS = 0x2, // '+'
    FLAG_PREFIX = 0x4, // 0x before the digits (%p)
    FLAG_LEFT = 0x8, // '-'
    FLAG_ZERO = 0x10, // '0'
    FLAG_LONG = 0x20, // l
    FLAG_SHORT = 0x40, // h
    FLAG_LONG_LONG = 0x80, // ll
    FLAG_CHAR = 0x100, // hh
    FLAG_UNSIGNED = 0x1000
};

extern "C" void FUN_00012EDA(Unk_000128F8* out, char c, s32 count);
extern "C" void FUN_00012F06(Unk_000128F8* out, char c);
extern "C" void FUN_00012F1E(Unk_000128F8* out, const char* src, s32 count);
extern "C" void* FUN_00013254(void* dst, const void* src, u32 size);

// vsnprintf: formats into buffer (at most size bytes with the NUL) and returns the length of the whole text. Knows
// %d %i %o %u %x %X %p %c %s %n %% with the flags ' ' '+' (taken only right after a ' ') '-' '0', a width and a
// precision (or *), and hh h l ll; copies Shift JIS characters through whole and anything else it does not know
// as it is.
s32 FUN_000128F8(char* buffer, u32 size, const char* format, std::va_list args)
{
    char digits[24];
    s32 n;
    char prefix[2];
    s32 prefixLen;
    const char* p = format;
    Unk_000128F8 out;
    out.len = size, out.cur = out.base = buffer;
    while (*p != 0) {
        if ((u32)(((u8)*p ^ 0x20) - 0xA1) < 0x3C) {
            // a Shift JIS lead byte (0x81-0x9F, 0xE0-0xFC) and the byte after it
            FUN_00012F06(&out, *p++);
            if (*p != 0)
                FUN_00012F06(&out, *p++);
        } else if (*p != '%') {
            FUN_00012F06(&out, *p++);
        } else {
            s32 flags = 0;
            s32 width = 0;
            s32 precision = -1;
            s32 base = 10;
            char hexBase = 'a' - 10; // digits 10-15 print as hexBase + digit
            const char* spec = p;
            for (;;) {
                switch (*++p) {
                case '+':
                    if (p[-1] != ' ')
                        break;
                    flags |= FLAG_PLUS;
                    continue;
                case ' ':
                    flags |= FLAG_SPACE;
                    continue;
                case '-':
                    flags |= FLAG_LEFT;
                    continue;
                case '0':
                    flags |= FLAG_ZERO;
                    continue;
                }
                break;
            }
            if (*p == '*') {
                ++p, width = __va_arg(args, s32);
                if (width < 0)
                    width = -width, flags |= FLAG_LEFT;
            } else {
                while (*p >= '0' && *p <= '9')
                    width = width * 10 + *p++ - '0';
            }
            if (*p == '.') {
                ++p, precision = 0;
                if (*p == '*') {
                    ++p, precision = __va_arg(args, s32);
                    if (precision < 0)
                        precision = -1;
                } else {
                    while (*p >= '0' && *p <= '9')
                        precision = precision * 10 + *p++ - '0';
                }
            }
            switch (*p) {
            case 'h':
                if (*++p != 'h')
                    flags |= FLAG_SHORT;
                else
                    ++p, flags |= FLAG_CHAR;
                break;
            case 'l':
                if (*++p != 'l')
                    flags |= FLAG_LONG;
                else
                    ++p, flags |= FLAG_LONG_LONG;
                break;
            }
            switch (*p) {
            case 'd':
            case 'i':
                goto number;
            case 'o':
                base = 8;
                flags |= FLAG_UNSIGNED;
                goto number;
            case 'u':
                flags |= FLAG_UNSIGNED;
                goto number;
            case 'X':
                hexBase = 'A' - 10;
                goto hex;
            case 'x':
                goto hex;
            case 'p':
                flags |= FLAG_PREFIX;
                precision = 8;
                goto hex;
            case 'c':
                if (precision >= 0)
                    goto other;
                {
                    s32 c = __va_arg(args, s32);
                    width -= 1;
                    if (flags & FLAG_LEFT) {
                        FUN_00012F06(&out, (char)c);
                        FUN_00012EDA(&out, ' ', width);
                    } else {
                        char pad = (char)((flags & FLAG_ZERO) ? '0' : ' ');
                        FUN_00012EDA(&out, pad, width);
                        FUN_00012F06(&out, (char)c);
                    }
                    ++p;
                }
                break;
            case 's': {
                s32 len = 0;
                const char* str = __va_arg(args, const char*);
                if (precision < 0) {
                    while (str[len])
                        ++len;
                } else {
                    while (len < precision && str[len])
                        ++len;
                }
                width -= len;
                if (flags & FLAG_LEFT) {
                    FUN_00012F1E(&out, str, len);
                    FUN_00012EDA(&out, ' ', width);
                } else {
                    char pad = (char)((flags & FLAG_ZERO) ? '0' : ' ');
                    FUN_00012EDA(&out, pad, width);
                    FUN_00012F1E(&out, str, len);
                }
                ++p;
                break;
            }
            case 'n': {
                s32 count = out.cur - out.base;
                if (flags & FLAG_CHAR)
                    ;
                else if (flags & FLAG_SHORT)
                    *__va_arg(args, s16*) = (s16)count;
                else if (flags & FLAG_LONG_LONG)
                    *__va_arg(args, s64*) = count;
                else
                    *__va_arg(args, s32*) = count;
                ++p;
                break;
            }
            case '%':
                if (spec + 1 != p)
                    goto other;
                FUN_00012F06(&out, *p++);
                break;
            default:
                goto other;
            other:
                FUN_00012F1E(&out, spec, p - spec);
                break;
            hex:
                base = 16;
                flags |= FLAG_UNSIGNED;
            number: {
                u64 value;
                FUN_00013254(&value, "\0\0\0\0\0\0\0", 8);
                prefixLen = 0;
                if (flags & FLAG_LEFT)
                    flags &= ~FLAG_ZERO;
                if (precision < 0)
                    precision = 1;
                else
                    flags &= ~FLAG_ZERO;
                if (flags & FLAG_UNSIGNED) {
                    if (flags & FLAG_CHAR) {
                        value = (u8)__va_arg(args, u32);
                    } else if (flags & FLAG_SHORT) {
                        value = (u16)__va_arg(args, u32);
                    } else if (flags & FLAG_LONG_LONG) {
                        __packed u64* arg = (__packed u64*)&value;
                        *arg = __va_arg(args, u64);
                    } else {
                        value = __va_arg(args, u32);
                    }
                    flags &= ~(FLAG_PLUS | FLAG_SPACE);
                    if (flags & FLAG_PREFIX) {
                        if (base == 16) {
                            if (value != 0) {
                                prefix[0] = hexBase + ('x' - 'a' + 10);
                                prefix[1] = '0';
                                prefixLen = 2;
                            }
                        } else if (base == 8) {
                            prefix[0] = '0';
                            prefixLen = 1;
                        }
                    }
                } else {
                    if (flags & FLAG_CHAR) {
                        value = (char)__va_arg(args, s32);
                    } else if (flags & FLAG_SHORT) {
                        value = (s16)__va_arg(args, s32);
                    } else if (flags & FLAG_LONG_LONG) {
                        __packed u64* arg = (__packed u64*)&value;
                        *arg = __va_arg(args, u64);
                    } else {
                        value = __va_arg(args, s32);
                    }
                    if ((value >> 32) & 0x80000000) {
                        value = ~value + 1;
                        prefix[0] = '-';
                        prefixLen = 1;
                    } else if (value || precision) {
                        if (flags & FLAG_PLUS) {
                            prefix[0] = '+';
                            prefixLen = 1;
                        } else if (flags & FLAG_SPACE) {
                            prefix[0] = ' ';
                            prefixLen = 1;
                        }
                    }
                }
                // the digits, last first
                n = 0;
                switch (base) {
                case 8:
                    while (value != 0) {
                        s32 d = (s32)(value & 7);
                        value >>= 3;
                        digits[n++] = (char)(d + '0');
                    }
                    break;
                case 10:
                    if ((value >> 32) == 0) {
                        u32 v = (u32)value;
                        while (v != 0) {
                            u32 q = v / 10;
                            s32 d = (s32)(v - q * 10);
                            v = q;
                            digits[n++] = (char)(d + '0');
                        }
                    } else {
                        while (value != 0) {
                            u64 q = value / 10;
                            s32 d = (s32)(value - q * 10);
                            __packed u64* next = (__packed u64*)&value;
                            *next = q;
                            digits[n++] = (char)(d + '0');
                        }
                    }
                    break;
                case 16:
                    while (value != 0) {
                        s32 d = (s32)(value & 0xF);
                        value >>= 4;
                        digits[n++] = (char)(d < 10 ? d + '0' : d + hexBase);
                    }
                    break;
                }
                // the octal prefix 0 counts as a digit
                if (prefixLen > 0 && prefix[0] == '0') {
                    prefixLen = 0;
                    digits[n++] = '0';
                }
            }
                {
                    s32 zeros = precision - n;
                    if (flags & FLAG_ZERO) {
                        if (zeros < width - n - prefixLen)
                            zeros = width - n - prefixLen;
                    }
                    if (zeros > 0)
                        width -= zeros;
                    width -= prefixLen + n;
                    if (!(flags & FLAG_LEFT))
                        FUN_00012EDA(&out, ' ', width);
                    while (prefixLen > 0)
                        FUN_00012F06(&out, prefix[--prefixLen]);
                    FUN_00012EDA(&out, '0', zeros);
                    while (n > 0)
                        FUN_00012F06(&out, digits[--n]);
                    if (flags & FLAG_LEFT)
                        FUN_00012EDA(&out, ' ', width);
                    ++p;
                }
                break;
            }
        }
    }
    if (out.len > 0)
        *out.cur = 0;
    else if (size > 0)
        out.base[size - 1] = 0;
    return out.cur - out.base;
}
