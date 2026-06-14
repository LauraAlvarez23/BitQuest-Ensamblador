bits 64
default rel

global caracteresMapa, validarMovimiento, puntaje, detectarObjeto, celdasLibres


section .text

caracteresMapa:
    ;Mete la informacion que tenia rsi a la pila (se utiliza el registro para recorrer la matriz)
    push rsi

    ;Limpia registro que contiene los datos a retornar 
    xor eax, eax    

    ;RCX = matrix
    ;EDX/RDX = nCeldas
    ;R8 = caracter

    xor rax, rax 
    lea rsi, [rcx]  ;rsi apunta al primer caracter de la matriz 

    .loop_matriz:
    ;Si el numero de celdas llego a 0, se acaba el loop
    cmp rdx, 0      
    je .fin_caracteresMapa

    ;Compara el valor al que apunta rsi con el caracter buscado
    cmp byte [rsi], r8b

    jne .siguiente      ;Si no es igual, va al siguiente caracter

    inc eax             ;Si es igual, se incrementa el contador

    .siguiente:
    ;rsi apunta al siguiente caracter, y se decrementa el numero de celdas
    inc rsi
    dec rdx
    jmp .loop_matriz

    .fin_caracteresMapa:
    ;rsi recupera su valor inicial al sacarlo de la pila
    pop rsi
    ret
    

validarMovimiento:
    ;Limpieza
    xor eax, eax

    ;RCX = matriz
    ;EDX/RDX = nColumnas
    ;R8 = fila
    ;R9 = columna
    

    ;PROXIMA POSICION = BASE + (FILA * nCOLUMNAS + COLUMNA)
    mov rax, r8     ;Se guarda el numero de fila en el registro rax para poder realizar la operacion

    ;rax = Fila * nColumnas
    imul rax, rdx   

    ;rax = Fila * nColumnas + Columna
    add rax, r9

    ;eax = Base + (Fila * nColumnas + Columna)
    movzx eax, byte[rcx + rax]  

    ;En la matriz, las paredes todavia se encuentran marcadas por #, 
    ;el caracter 219 no esta realmente en la matriz (es como una mascara)

    ;Valida si la proxima posicion es pared
    cmp al, '#'         
    je .mov_invalido

    ;Si no lo fue, se iguala a 0 el registro que se retornara
    mov eax, 0
    jmp .fin_validarMovimiento

    .mov_invalido:
    ;Si fue una pared, se iguala a 1 el registro que se retornara
    mov eax, 1

    .fin_validarMovimiento:
    ret


puntaje:
    ;PUNTAJE = (NIVEL * 1000) + (MONEDAS * 100) - (PASOS)

    ;RCX = numero de monedas
    ;EDX/RDX = pasos dados
    ;R8 = niveles

    ;Limpieza
    xor eax, eax

    ;Limia la parte alta de los registros
    mov ecx, ecx
    mov edx, edx
    mov r8d, r8d

    ;rax = Nivel * 1000
    mov rax, 1000
    imul rax, r8

    ;r9 = Monedas * 100
    mov r9, 100
    imul r9, rcx

    ;rax = rax + r9
    add rax, r9

    ;rax = rax - pasos dados
    sub rax, rdx

    ;Si el puntaje dio negativo, se mantiene en 0 para retornarlo
    cmp eax, 0
    jl .negativo
    jmp .fin_puntaje

    .negativo:
    mov eax, 0

    .fin_puntaje:
    ret  


detectarObjeto:
    ;Limpieza
    xor eax, eax

    ;RCX = matriz
    ;EDX/RDX = nColumnas
    ;R8 = fila
    ;R9 = columna
    ;pila[RSP + 40] = caracter

    ;PROXIMA POSICION = BASE + (FILA * nCOLUMNAS + COLUMNAS)
    mov rax, r8
    imul rax, rdx
    add rax, r9

   movzx eax, byte [rcx + rax]

    ;r10b = caracter buscado
   mov r10b, [rsp + 40]

    ;Si el caracter buscado es igual al caracter en la poscion calculada, se retorna un 1
    cmp al, r10b
    je .objeto_detectado

    ;Si no, se retorna un 0
    mov eax, 0
    jmp .fin_detectarObjeto

    .objeto_detectado:
    mov eax, 1

    .fin_detectarObjeto:
    ret


celdasLibres:
    ;Se va a usar rsi como indice de la matriz
    push rsi
    
    ;Limpieza
    xor eax, eax

    ;RCX = matrix
    ;EDX/RDX = nCeldas

    xor rax, rax 
    lea rsi, [rcx]  ;rsi apunta al inicio de la matriz 

    .loop_matriz:
    ;Si el numero de celdas llego a 0, acaba el loop
    cmp rdx, 0
    je .fin_celdasLibres

    ;Si el caracter al que rsi apunta es un '.' (una celda libre), incrementa el contador
    cmp byte [rsi], '.'
    je .es_libre

    ;Hace lo mismo si es una llave 
    cmp byte [rsi], 'K'
    je .es_libre

    ;O una moneda
    cmp byte [rsi], 184
    je .es_libre

    jmp .siguiente

    .es_libre:
    inc eax
    
    .siguiente:
    ;Avanza en la matriz y decrementa en numero de celdas
    inc rsi
    dec rdx
    jmp .loop_matriz

    .fin_celdasLibres:
    pop rsi
    ret

