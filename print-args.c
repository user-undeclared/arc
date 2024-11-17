#include "arc/standard_library.h"

Int main(String arguments[], Usize argument_count) {
    if(argument_count == 0) {
        chain_println("no arguments were provided");
        return 0;
    }

    printflnc("there were %z arguments provided", argument_count);
    for(Usize argument_index = 0; argument_index < argument_count; argument_index++) {
        printflnc("%02z: %s", argument_index, arguments[argument_index]);
    }
    return 0;
}
