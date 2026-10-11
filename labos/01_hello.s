; Labo 1 — Hello world en pur ASM x86_64 Linux
;
; Compile :  nasm -f elf64 01_hello.s -o 01_hello.o && ld 01_hello.o -o 01_hello
; Lance   :  ./01_hello
;
; Ce qu'il faut voir : 2 syscalls, le pattern "rax=numéro, args dans rdi/rsi/rdx, syscall".
; Référence des syscalls : https://x64.syscall.sh/

section .data
    msg db "hello depuis l'assembleur !", 0xa
    len equ $ - msg

section .text
global _start
_start:
    ; syscall write(fd=1, buf=msg, count=len)
    mov rax, 1              ; numéro du syscall write
    mov rdi, 1              ; fd 1 = stdout
    mov rsi, msg            ; adresse de la chaîne
    mov rdx, len            ; longueur
    syscall

    ; syscall exit(code=0)
    mov rax, 60             ; numéro du syscall exit
    mov rdi, 0              ; code de sortie
    syscall
