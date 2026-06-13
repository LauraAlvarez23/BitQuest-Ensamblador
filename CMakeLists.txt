cmake_minimum_required(VERSION 3.15)

project (BitQuest-Ensamblador LANGUAGES C ASM_NASM)

set(SOURCE
    src/main.c
    src/juego.c
    src/rutinas.asm
)

add_executable(BitQuest-Ensamblador ${SOURCE})
target_include_directories(BitQuest-Ensamblador PRIVATE include)

file(COPY
    assets/mapa1.txt
    assets/mapa2.txt
    assets/mapa3.txt
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
)