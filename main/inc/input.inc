;========= IP input =========
    mov rax, 1
    mov rdi, 1
    mov rsi, msg_ip
    mov rdx, msg_ip_len
    syscall

    xor r8, r8
.read_ip_byte:
    cmp r8, 16
    jge .read_ip_end
    mov rax, 0
    mov rdi, 0
    lea rsi, [ip_arg + r8]
    mov rdx, 1
    syscall
    test rax, rax
    jle .read_ip_end
    mov al, byte [ip_arg + r8]
    inc r8
    cmp al, 0xa
    jne .read_ip_byte
.read_ip_end:

;========= IP parsing =========
    mov rsi, 0
    mov rdi, ip_result - 4
    mov rcx, 4
    mov rdx, 0

.parse_ip:
    cmp byte [ip_arg + rsi], 0xa
    je .store_last_octet
    cmp byte [ip_arg + rsi], '.'
    je .store_octet

    movzx rax, byte [ip_arg + rsi]
    sub rax, '0'
    imul rdx, rdx, 10
    add rdx, rax
    inc rsi
    jmp .parse_ip

.store_octet:
    mov [rdi + rcx], dl
    inc rcx
    xor rdx, rdx
    inc rsi
    jmp .parse_ip

.store_last_octet:
    mov [rdi + rcx], dl

;========= Port input =========
    mov rax, 1
    mov rdi, 1
    mov rsi, msg_port
    mov rdx, msg_port_len
    syscall

    xor r8, r8
.read_port_byte:
    cmp r8, 8
    jge .read_port_end
    mov rax, 0
    mov rdi, 0
    lea rsi, [port_arg + r8]
    mov rdx, 1
    syscall
    test rax, rax
    jle .read_port_end
    mov al, byte [port_arg + r8]
    inc r8
    cmp al, 0xa
    jne .read_port_byte
.read_port_end:

;========= Port parsing =========
    xor rsi, rsi
    xor rax, rax

.parse_port:
    movzx rdx, byte [port_arg + rsi]
    cmp rdx, 0xa
    je .parse_port_done
    test rdx, rdx
    je .parse_port_done
    sub rdx, '0'
    imul rax, rax, 10
    add rax, rdx
    inc rsi
    jmp .parse_port

.parse_port_done:
    xchg al, ah
    mov [port_result], ax
