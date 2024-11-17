library_dir = arc
example_dir = examples

examples = $(patsubst %.c, %, $(wildcard $(example_dir)/*.c))

CFLAGS  += -Wall -Wextra -pedantic -Wno-main -fno-stack-protector -I . -std=c11 -g
LDFLAGS += -L $(library_dir)
LDLIBS  += -larc

.PHONY: all
all: $(examples)

.PHONY: clean
clean:
	$(RM) $(examples) $(example_dir)/*.o $(library_dir)/*.o $(library_dir)/*.a tags

$(example_dir)/%: $(example_dir)/%.o $(library_dir)/libarc.a
	$(LD) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(example_dir)/%.o: $(example_dir)/%.c
	$(CC) $(CFLAGS) -c $^ -o $@

$(library_dir)/libarc.a: $(library_dir)/start.o $(library_dir)/c_start.o $(library_dir)/standard_library.o
	$(AR) -rcs $@ $^

$(library_dir)/%.o: $(library_dir)/%.s
	$(AS) $^ -o $@

tags: *.c $(library_dir)/*.c $(library_dir)/*.h
	ctags $^
