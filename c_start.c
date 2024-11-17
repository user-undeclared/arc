#include "std.h"

Int _c_start(Ureg* stack_pointer) {
    const Byte** argument_chains = ((const Byte**) stack_pointer) + 1;
    Usize argument_count = *stack_pointer;

    String arguments[argument_count];
    for(Usize argument_index = 0; argument_index < argument_count; argument_index++) {
        arguments[argument_index] = string_from_chain(argument_chains[argument_index]);
    }

    Int exit_code = start(arguments, argument_count);
    print_buffer_flush();
    return exit_code;
}
