# BitQuest: Explorador de Matrices con C y NASM
##  - Proyecto de la materia Lenguaje Ensamblador -
## Equipo
- Rubén Altamira Martínez
- Aranza Arellano Delgado
- Laura Sofía Álvarez Huerta
- Jesús Eugenio Hernández Rodríguez 

## Requisitos de compilación
### Instalación de compiladores y herramientas
   Inicialmente se necesita tener instalado en compilador `MSYS2`, para eso podemos correr el siguiente comando en la terminal de windows:

```powershell
# Ejecutar el siguiente comando
winget install MSYS2.MSYS2
```
Ya terminada la instalación, busca en tu menú de inicio y abre la aplicación llamada `MSYS2 UCRT64`. Dentro se abrirá otra terminal, tipo linux.

Para lo demás necesitamos instalar los que es el compilador de `C (gcc)`, `NASM` y lo necesario para `CMake`. Por lo que en esta terminal ejecutaremos los siguientes comandos:

```bash
# Ejecutar los siguiente comando en orden
pacman -Syu
pacman -S mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-gdb mingw-w64-ucrt-x86_64-cmake mingw-w64-ucrt-x86_64-make mingw-w64-ucrt-x86_64-nasm
```

> [!WARNING]
> **Nota sobre la instalación en Windows**
> Es posible que durante la actualización o instalación de los paquetes, Windows Defender (o tu antivirus de terceros) intercepte y bloquee el ejecutable `pacman.exe`, denegando los permisos.
> 
> Si esto ocurre:
> 1. Agrega la carpeta de instalación (por defecto `C:\msys64`) a las exclusiones de tu antivirus.
> 2. Si el proceso de MSYS2 se rompió, desinstálalo, borra la carpeta residual y vuelve a instalarlo con la exclusión ya activa.
> 3. Si sigue sin funcionar, podemos a entrar a configuración > control inteligente de aplicaciones, y lo desactivamos.

### Configurar Variables de Entorno (PATH)

Para que la terminal y los scripts de compilación puedan encontrar los motores (`gcc`, `nasm`, etc.) automáticamente, es necesario agregar la ruta de MSYS2 al sistema:

1. Presiona `Win + R`, escribe `sysdm.cpl` y presiona **Enter**.
2. Ve a la pestaña **Opciones avanzadas** y haz clic en el botón **Variables de entorno...**.
3. En la sección inferior (**Variables del sistema**), busca la variable llamada `Path`, selecciónala y haz clic en **Editar**.
4. Haz clic en **Nuevo** y pega la siguiente ruta exacta:
   ```text
   C:\msys64\ucrt64\bin
   ```
5. Haz clic en **Aceptar** en todas las ventanas para guardar los cambios.

> [!NOTE]
> **Importante:** Si tenías la terminal o tu editor de código abierto durante este proceso, deberás cerrarlo y volverlo a abrir para que reconozca el nuevo PATH. Puedes verificar que funcionó ejecutando `gcc --version` en tu consola.

## Compilación con CMake

Este proyecto utiliza CMake para gestionar la construcción del ejecutable, enlazando automáticamente el código fuente en C y las rutinas de Ensamblador.

1. Abre una terminal (PowerShell, CMD o la integrada del editor) en la carpeta raíz del proyecto.
2. Genera los archivos de construcción especificando el entorno de MinGW:
   ```powershell
   cmake -S . -B build -G "MinGW Makefiles"
   ```
3. Compila el proyecto:
   ```powershell
   cmake --build build
   ```

> [!NOTE]
> Al terminar, CMake habrá creado una carpeta oculta llamada `build` donde se encontrará el archivo final compilado.

---

## Ejecución del Juego

Una vez que la compilación haya sido exitosa, puedes iniciar el laberinto ejecutando el archivo generado directamente desde la terminal:

```powershell
.\build\BitQuest-Ensamblador.exe
```
