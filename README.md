# EXAMEN FINAL INTEGRADOR - SIS-112
## Proyecto: Producción y Entrega de Contenido Multimedia (Grupo 10)

**Asignatura:** Programación I (SIS-112)  
**Docente:** Pamela Shirley Valenzuela Fernández  
**Gestión:** 1/2026  

### 👩‍💻 Integrantes del Equipo
* **Carla**
* **Nicole**

---

## 1. Visión General y Dominio de Datos
El proyecto simula la gestión interna de una agencia creativa que produce contenido multimedia. El sistema ayuda a registrar entregas, buscar proyectos de forma eficiente y comparar algoritmos de ordenamiento para optimizar las prioridades de entrega basadas en las fechas límite.

### Estructura de Datos (El `struct` Content)
Para cumplir con el **CRUD en archivos binarios (.dat)**, se ha diseñado una estructura de datos estática utilizando arreglos de caracteres (`char[]`). Esto es fundamental porque permite calcular un `sizeof(Content)` exacto en memoria, facilitando las lecturas y escrituras directas (`fread`/`fwrite`).

```cpp
struct Content {
    int id;                      // Identificador único y autoincremental
    char contenido[100];         // Título o descripción del contenido (ej. "Spot Publicitario")
    char tipo[30];               // Tipo: VIDEO, ANIMACION, IMAGEN
    char cliente[50];            // Nombre del cliente
    char fecha_entrega[15];      // Fecha límite (formato YYYY-MM-DD) para ordenamientos
    char estado[30];             // EN PROCESO, ENTREGADO o PENDIENTE DE REVISION
    char observaciones[150];     // Notas técnicas adicionales
};
```

---

## 2. Requisitos Cumplidos (Grupo 10)

El código fuente ha sido optimizado **exclusivamente** para cubrir los puntos asignados al Grupo 10 en la rúbrica del examen:

* **Dimensión 1 (Estructura y Parámetros):** Todo el código está fuertemente modularizado en librerías propias (`production.h`, `fileio.h`, `menu.h`, `utils.h`). Se hace uso de funciones robustas y control de paso por parámetros.
* **Dimensión 2 (Algoritmia Avanzada):** 
  * Se implementó un Módulo Comparativo de Ordenación que evalúa la eficiencia entre **Bubble Sort Optimizada** e **Intercalación (Merge Sort)** ordenando las entregas cronológicamente por su `fecha_entrega` límite.
  * Se implementó la **Búsqueda Binaria** en dos versiones: Iterativa y Recursiva. Busca proyectos por `id` e informa cuántas iteraciones/llamadas se realizaron.
* **Dimensión 3 (Almacenamiento Físico):** 
  * **Seeding:** Al iniciar, se cargan 10 registros automáticos directamente en binario.
  * **CRUD 100% Binario:** Alta, baja, modificación y listado actúan de forma directa y persistente en `data/proyectos.dat`.
  * **Reporte Exportable:** Se generan salidas formateadas en `.csv` para compatibilidad con Excel.

---

## 3. Arquitectura del Proyecto

Para mantener el orden y evitar colisiones de dependencias, se usó el paradigma modular de C++:
* 📂 `include/`: Contiene los *headers* (`.h`). Aquí se declaran los prototipos (`production.h`, `fileio.h`, `utils.h`, `menu.h`).
* 📂 `src/`: Contiene las implementaciones técnicas (`.cpp`) correspondientes a las cabeceras, separando toda la lógica por módulos.
* 📂 `data/`: Directorio donde el sistema guarda físicamente la base de datos `proyectos.dat`.
* 📄 `main.cpp`: Es el punto de entrada, sumamente limpio, cuya única instrucción es mandar a llamar a `Menu::runApp()`.
* 📄 `PROYECTO FINAL.dev`: Archivo de entorno listo para **Dev-C++**, mapeado con la estructura modular completa.

---

## 4. Guía de Compilación y Ejecución

Para una guía detallada y resolución de problemas del compilador en Dev-C++, consulta el [Manual de Compilación y Ejecución](file:///c:/Users/saenz/OneDrive/Desktop/POGRAMACION%20MULTIMEDIA/MANUAL_EJECUCION.md).

### Opción 1: Compilación Automática (Recomendado)
Simplemente haz doble clic en el archivo [ejecutar_proyecto.bat](file:///c:/Users/saenz/OneDrive/Desktop/POGRAMACION%20MULTIMEDIA/ejecutar_proyecto.bat). Este script buscará el compilador automáticamente, compilará el código y lo ejecutará en una consola de comandos con soporte para caracteres especiales.

### Opción 2: A través de Dev-C++
Abre el archivo [PROYECTO FINAL.dev](file:///c:/Users/saenz/OneDrive/Desktop/POGRAMACION%20MULTIMEDIA/PROYECTO%20FINAL.dev) en Dev-C++ y presiona **F11** (Ejecutar -> Compilar y Ejecutar). 
*Nota: Asegúrate de habilitar el soporte de **C++11** en la configuración de Dev-C++ (Menú Herramientas -> Opciones del Compilador -> Configuración -> Generación de Código -> Estándar de Lenguaje -> ISO C++11).*

### Opción 3: A través de Consola (G++)
Abre la terminal en la raíz del proyecto y ejecuta:
```bash
g++ -std=c++11 -Wall -Wextra main.cpp src/*.cpp -o programa.exe
```
Luego ejecuta `./programa.exe`.


---

## 5. Manual de Usuario Rápido

Al ejecutar el programa, serás recibida por el Menú Principal con 10 opciones.

* **Opciones 1 al 4 (Gestión de Entregas):** El CRUD básico. Permite agregar nuevos proyectos multimedia, listarlos en una tabla (que siempre se auto-ordena por fecha), modificar sus atributos o eliminarlos. Todo se guarda automáticamente en `proyectos.dat`.
* **Opción 5 (Reporte Comparativo):** Ordena los datos por la "Fecha Límite". Te mostrará en pantalla una tabla indicando qué algoritmo (Merge o Bubble) hizo menos operaciones.
* **Opción 6 (Búsqueda por ID):** Busca mediante Búsqueda Binaria Recursiva o Iterativa. En caso de no estar ordenado previamente, invoca a Bubble Sort en silencio antes de buscar.
* **Opción 7 (Reporte Exportable CSV):** Genera un archivo `.csv` compatible con Excel con toda la base de datos de manera ordenada.
* **Opciones 8 y 9:** Utilidades para guardar y cargar manualmente la base de datos en `proyectos.dat`.
