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
    ;R8 = fila
    ;R9 = columna
    

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

puntaje:
    ;   PUNTAJE = (NIVEL * 1000) + (MONEDAS * 100) - (PASOS)

    ;RCX = numero de monedas
    ;EDX/RDX = pasos dados
    ;R8 = niveles


    ;Limpieza
    xor eax, eax

    mov ecx, ecx
    mov edx, edx
    mov r8d, r8d

    mov rax, 1000
    imul rax, r8

    mov r9, 100
    imul r9, rcx

    add rax, r9
    sub rax, rdx

    cmp eax, 0
    jl .negativo
    jmp .fin_puntaje

    .negativo:
    mov eax, 0

    .fin_puntaje:
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

celdasLibres:
   push rsi
    xor eax, eax

    ;RCX = matrix
    ;EDX/RDX = nCeldas

    xor rax, rax 
    lea rsi, [rcx]

    .loop_matriz:
    cmp rdx, 0
    je .fin_celdasLibres

    cmp byte [rsi], '.'
    je .es_libre

    cmp byte [rsi], 'K'
    je .es_libre

    jmp .siguiente

    .es_libre:
    inc eax
    
    .siguiente:
    inc rsi
    dec rdx
    jmp .loop_matriz


    .fin_celdasLibres:
    pop rsi
    ret

