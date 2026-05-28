bits 64
default rel

global caracteresMapa, validarMovimiento, puntaje, detectarObjeto, celdasLibres


section .text

caracteresMapa:
    push rsi
    xor eax, eax

    ;RCX = matrix
    ;EDX/RDX = nCeldas
    ;R8 = caracter

    xor rax, rax 
    lea rsi, [rcx]

    .loop_matriz:
    cmp rdx, 0
    je .fin_caracteresMapa

    cmp byte [rsi], r8b
    jne .siguiente

    inc eax

    .siguiente:
    inc rsi
    dec rdx
    jmp .loop_matriz

    .fin_caracteresMapa:
    pop rsi
    ret
    

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

    cmp al, '#'         ;En la matriz, las paredes todavia se encuentran marcadas por #, el caracter 219 no esta realmente en la matriz (es como una mascara)
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