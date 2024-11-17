#ifndef STD_H_
#define STD_H_

#include <stdarg.h>

// TODO: make Byte an unsigned char and make Char a char
typedef unsigned long Usize;
typedef unsigned long Ureg;
typedef          long Ireg;
// typedef unsigned char Byte;
// typedef          char Char;
typedef          char Byte;
typedef unsigned int  Uint;
typedef          int  Int;
typedef _Bool         Bool;

#define NULL ((void*) 0)
#define false (-1 == 0)
#define true (!false)

Int start();

typedef struct {
    const Byte* bytes;
    Usize length;
} String;

// TODO: find a better name for nul-terminated strings than "chain"
Usize chain_get_length(const Byte* chain);
Bool chain_print(const Byte* message);
Bool chain_println(const Byte* message);

String string_from_chain(const Byte* chain);
String string_temporary_from_usize(Usize usize);
Bool string_to_usize(Usize* result, Uint* result_digit_count, String string);

Bool print_buffer_flush(void);
Bool print_byte(Byte byte);
Bool print(String message);
Bool println(String message);
// TODO: name these *printf* procedures better while keeping their names short
Bool vprintfc(const Byte* fmt, va_list argument_list);
Bool printflnc(const Byte* fmt, ...);

#endif
