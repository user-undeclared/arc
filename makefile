library_name = arc

library_dir = $(library_name)
example_dir = examples

library  = $(library_dir)/lib$(library_name).a
examples = $(patsubst %.c, %, $(wildcard $(example_dir)/*.c))

CFLAGS  += -Wall -Wextra -pedantic -Wno-main \
           -nostdlib -fno-stack-protector -fno-builtin \
           -I . -std=c11
LDFLAGS += -L $(library_dir)
LDLIBS  += -l$(library_name)

.PHONY: all library examples clean
all: library examples

library: $(library)

examples: $(examples)

clean:
	$(RM) $(examples) $(example_dir)/*.o $(library_dir)/*.o $(library_dir)/*.a tags

$(library): $(library_dir)/start.o $(library_dir)/c_start.o $(library_dir)/standard_library.o
	$(AR) -rcs $@ $^

$(library_dir)/%.o: $(library_dir)/%.s
	$(AS) $^ -o $@

$(example_dir)/%: $(example_dir)/%.o $(library)
	$(LD) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(example_dir)/%.o: $(example_dir)/%.c
	$(CC) $(CFLAGS) -c $^ -o $@

tags: $(library_dir)/*.c $(library_dir)/*.h
	ctags $^
