default abs

%include "main/inc/data.inc"

section .text
global _start

_start:
    pop rax
    cmp rax, 2
    jne error

    pop rsi
    pop rax
    mov [file_name], rax
    xor rax, rax

%include "main/inc/input.inc"

    xor rax, rax

    ; Open target file (read/write)
    mov rax, 2
    mov rdi, [file_name]
    mov rsi, 2
    syscall

    test rax, rax
    js error

    mov [file_descriptor], rax

    ; Read ELF header into buffer
    mov rax, 0
    mov rdi, [file_descriptor]
    mov rsi, buffer
    mov rdx, 2000
    syscall

    mov rdi, 1
    mov rax, 1
    mov rsi, msg_start
    mov rdx, msg_start_len
    syscall

    xor r15, r15
    xor r9, r9
    mov r9, buffer
    xor rcx, rcx

    ; Get file size via lseek
    mov rax, 8
    mov rdi, [file_descriptor]
    mov rsi, 0
    mov rdx, 1
    syscall

    mov rbx, rax

    mov rax, 8
    mov rdi, [file_descriptor]
    mov rsi, 0
    mov rdx, 2
    syscall

    mov [file_size], rax

    ; Reset cursor
    mov rax, 8
    mov rdi, [file_descriptor]
    mov rsi, 0
    mov rdx, 0
    syscall

%include "main/inc/elf_patcher.inc"

%include "main/inc/injector.inc"

sortie:
    mov rax, 3
    syscall

    mov rdi, 1
    mov rax, 1
    mov rsi, msg_done
    mov rdx, msg_done_len
    syscall

    mov rax, 60
    mov rdi, 0
    syscall

error:
    mov rax, 1
    mov rdi, 1
    mov rsi, msg_error
    mov rdx, msg_error_len
    syscall

    mov rax, 60
    mov rdi, 1
    syscall
