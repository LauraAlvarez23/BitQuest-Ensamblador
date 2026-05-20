bits 64
default rel

global caracteresMapa, validarMovimiento, puntaje, detectarObjeto, celdasLibres


section .text
validarMovimiento:
    xor eax, eax

    ;RCX = matriz
    ;EDX/RDX = nColumnas
    ;R9 = columna
    ;R8 = fila

    ;PROXIMA DIRECCION = BASE + (FILA * nCOLUMNAS + COLUMNAS)
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

detectarObjeto:
    xor eax, eax

    ;RCX = matriz
    ;EDX/RDX = nColumnas
    ;R9 = columna
    ;R8 = fila
    ;pila[RSP + 40] = caracter

    ;PROXIMA DIRECCION = BASE + (FILA * nCOLUMNAS + COLUMNAS)
    mov rax, r8
    imul rax, rdx
    add rax, r9

   movzx eax, byte [rcx + rax]

   mov r10b, [rsp + 40]

    cmp al, r10b
    je .objeto_detectado

    mov eax, 0
    jmp .fin_detectarObjeto

    .objeto_detectado:
    mov eax, 1

    .fin_detectarObjeto:
    ret