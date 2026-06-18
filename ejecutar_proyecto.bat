@echo off
:: Permite ver caracteres especiales como acentos y eñes
chcp 65001 > nul
title Compilador y Ejecutor Automatico - Proyecto Final C++
echo =================================================================
echo        COMPILADOR Y EJECUTOR AUTOMATICO - GRUPO 10
echo =================================================================
echo.

:: Buscar la herramienta que convierte el codigo en un programa ejecutable (g++.exe)
set "COMPILER="

:: 1. Intentar buscar en las configuraciones principales de la computadora
where g++ >nul 2>nul
if %errorlevel% equ 0 (
    set "COMPILER=g++"
    goto found
)

:: 2. Intentar buscar en la carpeta de Dev-C++ (version de 64 bits)
if exist "C:\Program Files (x86)\Dev-Cpp\MinGW64\bin\g++.exe" (
    set "COMPILER=C:\Program Files (x86)\Dev-Cpp\MinGW64\bin\g++.exe"
    goto found
)

:: 3. Intentar buscar en otra carpeta común de Dev-C++
if exist "C:\Program Files\Dev-Cpp\MinGW64\bin\g++.exe" (
    set "COMPILER=C:\Program Files\Dev-Cpp\MinGW64\bin\g++.exe"
    goto found
)

:: 4. Intentar buscar en la version Embarcadero Dev-C++
if exist "C:\Program Files (x86)\Embarcadero\Dev-Cpp\TDM-GCC\bin\g++.exe" (
    set "COMPILER=C:\Program Files (x86)\Embarcadero\Dev-Cpp\TDM-GCC\bin\g++.exe"
    goto found
)

:: Si no lo encuentra, avisa al usuario para que instale o configure Dev-C++
:not_found
echo [ERROR] No se pudo encontrar el compilador g++ en el sistema.
echo.
echo Por favor, asegúrate de que Dev-C++ esté instalado en la ruta por defecto:
echo C:\Program Files (x86)\Dev-Cpp
echo O agrega la carpeta 'bin' del compilador a la variable de entorno PATH del sistema.
echo.
pause
exit /b 1

:: Si lo encontró, avisa y empieza a crear el programa
:found
echo [OK] Compilador encontrado: "%COMPILER%"
echo.
echo [COMPILANDO] Compilando el proyecto final para que puedas usarlo...
echo.

:: Crea una carpeta llamada 'data' para guardar información, solo si no existe todavia
if not exist "data" (
    mkdir "data"
)

:: Une todos los archivos de codigo en un solo programa llamado 'programa.exe'
"%COMPILER%" -std=c++11 -Wall -Wextra -Iinclude main.cpp src/production.cpp src/fileio.cpp src/utils.cpp src/menu.cpp -o programa.exe

:: Si hay algun error al crear el programa, avisa al usuario y se detiene
if %errorlevel% neq 0 (
    echo.
    echo [ERROR] La compilación falló. Revisa los mensajes de arriba.
    echo.
    pause
    exit /b 1
)

:: Si todo salió bien, abre el programa
echo [OK] Compilación exitosa. Generado: programa.exe
echo.
echo =================================================================
echo                   EJECUTANDO EL PROGRAMA
echo =================================================================
echo.

programa.exe

echo.
echo =================================================================
echo [FIN] El programa ha finalizado.
echo =================================================================
pause
