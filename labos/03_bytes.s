; Labo 3 — Jouer avec les octets
;
; Compile :  nasm -f elf64 03_bytes.s -o 03_bytes.o && ld 03_bytes.o -o 03_bytes
; Lance   :  ./03_bytes
;
; Montre que "écrire des octets, c'est juste écrire des nombres".
; Les octets sont interprétés comme du texte ASCII par le terminal :
;   0x41 = 'A', 0x42 = 'B', 0x43 = 'C', 0x44 = 'D', 0x0a = '\n' (newline)
;
; Exercice : remplace 0x41 par 0x61 (= 'a' minuscule). Ça affichera "aBCD".
; Table ASCII pour s'amuser : https://www.ascii-code.com/

section .data
    val db 0x41, 0x42, 0x43, 0x44, 0x0a    ; 5 octets : A, B, C, D, newline
    len equ $ - val

section .text
global _start
_start:
    mov rax, 1
    mov rdi, 1
    mov rsi, val
    mov rdx, len
    syscall

    mov rax, 60
    xor rdi, rdi                            ; équivalent à mov rdi, 0 (plus court)
    syscall
