.extern _c_start

.set SYSCALL_EXIT,  60
.set STDOUT_FILENO, 1

.text
.globl _start
_start:
    mov %rsp, %rdi
    call _c_start
    jmp _exit

.globl _exit
_exit:
    mov $SYSCALL_EXIT, %eax
    syscall

.globl _write
_write:
    mov %rsi, %rdx
    mov %rdi, %rsi
    mov $STDOUT_FILENO, %eax
    mov %eax, %edi
    syscall
    ret
