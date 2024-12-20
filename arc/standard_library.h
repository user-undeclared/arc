#ifndef STANDARD_LIBRARY_H_
#define STANDARD_LIBRARY_H_

#include <stddef.h>
#include <stdbool.h>
#include <stdarg.h>

typedef unsigned long Usize;
typedef unsigned long Ureg;
typedef          long Ireg;
typedef unsigned char Byte;
typedef          char Char;
typedef unsigned int  Uint;
typedef          int  Int;
typedef          bool Bool;

typedef const char* Chain;

// TODO: find a better name for nul-terminated strings than "chain"
Usize chain_get_length(Chain chain);
Bool chain_print(Chain message);
Bool chain_println(Chain message);

typedef struct {
    const Byte* bytes;
    Usize byte_count;
} String;

String string_from_chain(Chain chain);
String string_temporary_from_usize(Usize usize);
Bool string_to_usize(Usize* result, Uint* result_digit_count, String string);

Bool print_buffer_flush(void);
Bool print_byte(Byte byte);
Bool print(String message);
Bool println(String message);
// TODO: name these *printf* procedures better while keeping their names short
Bool vprintfc(Chain fmt, va_list argument_list);
Bool printflnc(Chain fmt, ...);

#endif
