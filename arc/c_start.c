#include "standard_library.h"

Int main(String arguments[], Usize argument_count);

Int _c_start(Ureg* stack_pointer) {
    Chain* argument_chains = ((Chain*) stack_pointer) + 1;
    Usize argument_count = *stack_pointer;

    String arguments[argument_count];
    for(Usize argument_index = 0; argument_index < argument_count; argument_index++) {
        arguments[argument_index] = string_from_chain(argument_chains[argument_index]);
    }

    Int exit_code = main(arguments, argument_count);
    print_buffer_flush();
    return exit_code;
}
