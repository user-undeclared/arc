.POSIX:

lib_dir = arc

CFLAGS  += -Wall -Wextra -pedantic -Wno-main -fno-stack-protector -std=c11 -g
LDFLAGS += -L $(lib_dir)
LDLIBS  += -lthing

all: hello print-args

hello: hello.o $(lib_dir)/libthing.a
	$(LD) $(LDFLAGS) $(LDLIBS) $^ -o $@

print-args: print-args.o $(lib_dir)/libthing.a
	$(LD) $(LDFLAGS) $(LDLIBS) $^ -o $@

$(lib_dir)/libthing.a: $(lib_dir)/start.o $(lib_dir)/c_start.o $(lib_dir)/standard_library.o
	$(AR) -rcs $@ $^

$(lib_dir)/start.o: $(lib_dir)/start.asm
	fasm $^

tags: *.c $(lib_dir)/*.c $(lib_dir)/*.h
	ctags $^

.PHONY: clean
clean:
	$(RM) hello print-args *.o $(lib_dir)/*.o $(lib_dir)/*.a tags
