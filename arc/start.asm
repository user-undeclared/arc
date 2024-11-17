format ELF64

SYSCALL_EXIT  equ 60
STDOUT_FILENO equ 1

extrn _c_start

section ".text" executable
public _start
_start:
    mov rdi, rsp
    call _c_start
    jmp _exit

public _exit
_exit:
    mov eax, SYSCALL_EXIT
    syscall

public _write
_write:
    mov rdx, rsi
    mov rsi, rdi
    mov eax, STDOUT_FILENO
    mov edi, eax
    syscall
    ret
