#include "std.h"

Usize chain_get_length(Chain chain) {
    if(chain == NULL) {
        return 0;
    }
    Usize chain_length = 0;
    while(chain[chain_length] != '\0') {
        chain_length++;
    }
    return chain_length;
}

String string_from_chain(Chain chain) {
    return (String) {
        .bytes = (Byte*) chain,
        .byte_count = chain_get_length(chain),
    };
}

String string_temporary_from_usize(Usize usize) {
    // 20 = ceil(log10(1 << (sizeof(Usize) * CHAR_BIT))
    static Byte buffer[20];
    String result = {
        .bytes = buffer,
        .byte_count = 0,
    };
    if(usize == 0) {
        buffer[0] = '0';
        result.byte_count = 1;
        return result;
    }
    for(Usize accumulator = usize; accumulator > 0; accumulator /= 10) {
        Byte base_ten_ones_place = accumulator % 10;
        Byte digit = base_ten_ones_place + '0';
        buffer[result.byte_count] = digit;
        result.byte_count++;
    }
    for(Usize byte_index = 0; byte_index < result.byte_count / 2; byte_index++) {
        Byte temp = buffer[result.byte_count - byte_index - 1];
        buffer[result.byte_count - byte_index - 1] = buffer[byte_index];
        buffer[byte_index] = temp;
        
    }
    return result;
}

Bool string_to_usize(Usize* result, Uint* result_digit_count, String string) {
    if(string.bytes == NULL) {
        return false;
    }

    Usize accumulator = 0;
    Usize digit_index = 0;
    for(; digit_index < string.byte_count; digit_index++) {
        Byte digit = string.bytes[digit_index];
        if(digit < '0' || digit > '9') {
            break;
        }
        Byte base_ten_ones_place = digit - '0';
        accumulator = (accumulator * 10) + base_ten_ones_place;
    }
    if(digit_index == 0) {
        return false;
    }

    if(result != NULL) {
        *result = accumulator;
    }
    if(result_digit_count != NULL) {
        *result_digit_count = digit_index;
    }
    return true;
}

Int _write(const Byte* bytes, Usize byte_count);
void _exit(Int exit_code);

#define _PRINT_BUFFER_CAPACITY 1024
typedef struct {
    Byte bytes[_PRINT_BUFFER_CAPACITY];
    Usize byte_count;
} Print_Buffer;
static Print_Buffer _print_buffer;

Bool print_buffer_flush(void) {
    Ireg bytes_written = _write(_print_buffer.bytes, _print_buffer.byte_count);
    return bytes_written > 0 || (Ureg) bytes_written == _print_buffer.byte_count;
}

Bool print_byte(Byte byte) {
    Bool byte_will_fill_print_buffer = _print_buffer.byte_count + 1 >= _PRINT_BUFFER_CAPACITY;
    Bool byte_is_newline = byte == '\n';
    if(byte_will_fill_print_buffer || byte_is_newline) {
        if(byte_is_newline) {
            _print_buffer.bytes[_print_buffer.byte_count] = byte;
            _print_buffer.byte_count += 1;
        }
        if(!print_buffer_flush()) {
            return false;
        }
        _print_buffer.byte_count = 0;
        if(byte_is_newline) {
            return true;
        }
    }

    _print_buffer.bytes[_print_buffer.byte_count] = byte;
    _print_buffer.byte_count += 1;
    return true;
}

Bool print(String message) {
    for(Usize byte_index = 0; byte_index < message.byte_count; byte_index++) {
        if(!print_byte(message.bytes[byte_index])) {
            return false;
        }
    }
    return true;
}

Bool println(String message) {
    return print(message) && print_byte('\n');
}

Bool chain_print(Chain message) {
    return print(string_from_chain(message));
}

Bool chain_println(Chain message) {
    return println(string_from_chain(message));
}

Bool vprintfc(Chain fmt, va_list argument_list) {
    String format = string_from_chain(fmt);
    const Byte* bytes_end = format.bytes + format.byte_count;
    const Byte* byte = format.bytes;
    while(byte < bytes_end) {
        if(*byte != '%') {
            print_byte(*byte);
            byte++;
            continue;
        }

        byte++;
        if(byte >= bytes_end) {
            return false;
        }

        Byte flag = *byte;
        byte++;
        switch(flag) {
            case '0':
            case ' ': {
                Byte padding_byte = flag;
                Usize padding;
                Uint padding_digit_count;
                String padding_string = {
                    .bytes = byte,
                    .byte_count = bytes_end - byte,
                };
                if(!string_to_usize(&padding, &padding_digit_count, padding_string)) {
                    return false;
                }

                byte += padding_digit_count;
                if(byte >= bytes_end) {
                    return false;
                }

                switch(*byte++) {
                    case 'z': {
                        Usize argument = va_arg(argument_list, Usize);
                        String argument_string = string_temporary_from_usize(argument);
                        for(Uint padding_index = argument_string.byte_count; padding_index < padding; padding_index++) {
                            print_byte(padding_byte);
                        }
                        print(argument_string);
                        break;
                    }
                    default: {
                        return false;
                    }
                }
                break;
            }
            case 's': {
                String argument = va_arg(argument_list, String);
                print(argument);
                break;
            }
            case 'z': {
                Usize argument = va_arg(argument_list, Usize);
                String argument_string = string_temporary_from_usize(argument);
                print(argument_string);
                break;
            }
            default: {
                return false;
            }
        }
    }

    return 0;
}

Bool printflnc(Chain fmt, ...) {
    va_list argument_list;
    va_start(argument_list, fmt);
    Bool result = vprintfc(fmt, argument_list);
    print_byte('\n');
    va_end(argument_list);
    return result;
}
