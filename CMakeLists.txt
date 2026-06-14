# Version minima requerida de CMake para compilar el proyecto
cmake_minimum_required(VERSION 3.15)

#set(CMAKE_ASM_NASM_COMPILER "C:/nasm/nasm.exe")  # <- Para Laura que no le funcionaba (ya si)

# Nombre del proyecto y lenguajes que usa -
project (BitQuest-Ensamblador LANGUAGES C ASM_NASM)

# Archivos fuente del proyecto
set(SOURCE
    src/main.c
    src/juego.c
    src/rutinas.asm
)

# Crea el ejecutable con los archivos fuente
add_executable(BitQuest-Ensamblador ${SOURCE})
# Agrega /include para que el compilador encuentre las cabeceras .h
target_include_directories(BitQuest-Ensamblador PRIVATE include)

# Copia los mapas solo cuando hay cambios en ellos
configure_file(assets/mapa1.txt mapa1.txt COPYONLY)
configure_file(assets/mapa2.txt mapa2.txt COPYONLY)
configure_file(assets/mapa3.txt mapa3.txt COPYONLY)