# ARC: **A**nother **R**untime for **C**

> [!WARNING]
> this library was hacked out in two nights, and development may not continue,
> so very little is implemented and it only works on x86\_64 gnu/linux systems

this library provides an alternative runtime and associated standard library for
c programs that can be used instead of the default one(s)

this library also takes advantage of the c99 standard and also tries not to use
nul-terminated strings (which are called chains in this library), with it
prefering to use sized strings whenever possible

finally, this library is written in my preferred coding style, which includes
making every type start with a capital letter, including primitives

## building

at the moment, this library only depends on the usual tools needed to compile c
on gnu/linux. to build the code, there is a [`makefile`](./makefile) that can be used
directly or referenced if building manually

to just build everything with `make`, run
```console
$ make
```
