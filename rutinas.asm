bits 64
default rel

global caracteresMapa, validarMovimiento, puntaje, detectarObjeto, celdasLibres


section .text
validarMovimiento:
    xor eax, eax

    mov rax, r8
    imul rax, rdx

    add rax, r9

    movzx eax, byte[rcx + rax]

    cmp al, '#'
    je .mov_invalido

    mov eax, 0
    jmp .fin_validarMovimiento

    .mov_invalido:
    mov eax, 1

    .fin_validarMovimiento:
    ret