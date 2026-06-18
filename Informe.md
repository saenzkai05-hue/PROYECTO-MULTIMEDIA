# INFORME DE PROYECTO
## Persistencia de los Datos

**UNIVERSIDAD CATÓLICA BOLIVIANA “SAN PABLO”**  
Facultad de Ingeniería — Departamento de Ingeniería de Sistemas

**Asignatura:** Programación I (SIS-112)  
**Gestión:** 1/2026  
**Paralelo:** 3  
**Docente:** Pamela Shirley Valenzuela Fernandez

**Título del Proyecto:** Control de Producción y Entrega de Contenido Multimedia  
**Área / Carrera:** Diseño Digital

### Integrantes del Grupo:
* **Integrante 1:** Nicole Hernández
* **Integrante 2:** Carla Saenz

**Fecha de entrega:** 08/06/2026

---

## 1. Introducción / Justificación

El presente proyecto consiste en el desarrollo de un sistema en C++ para la gestión del ciclo de producción y entrega de contenido multimedia (videos, animaciones e imágenes) dentro de una empresa o equipo creativo. El objetivo general es organizar y automatizar el control de los contenidos, permitiendo registrar, consultar, modificar, eliminar y filtrar información relevante como el tipo de contenido, cliente, fecha de entrega, estado y observaciones.

Este tema fue elegido porque los diseñadores digitales manejan múltiples proyectos simultáneamente, y contar con una herramienta de software que evite el desorden y facilite el seguimiento de cada encargo es fundamental para optimizar los flujos de trabajo. El sistema aplica los conceptos de persistencia de datos mediante archivos binarios (`proyectos.dat`), operaciones CRUD (crear, leer, actualizar, eliminar) sobre un arreglo de estructuras, así como algoritmos de ordenamiento (Bubble Sort y Merge Sort) y búsqueda (binaria iterativa y recursiva) sobre campos como fecha de entrega o identificador. De esta forma, se demuestra cómo la programación en C++ puede resolver problemas reales del ámbito del diseño digital.

---

## 2. Descripción del Dominio del Problema

El problema que resuelve el sistema es la falta de control organizado sobre los contenidos multimedia que un estudio produce para distintos clientes. Sin una herramienta automatizada, resulta difícil saber qué contenido está en proceso, cuál ya fue entregado o cuál presenta errores técnicos. El sistema gestiona datos como: nombre del contenido, tipo (video, animación, imagen), cliente, fecha de entrega, estado y observaciones. Estos datos son relevantes para la carrera de Diseño Digital porque simulan el entorno real de producción de una agencia o departamento creativo.

| Campo | Valor |
|---|---|
| **Nombre del sistema:** | Control de producción y entrega de contenido multimedia |
| **Carrera relacionada:** | Diseño Digital |
| **Problema que resuelve:** | Organización y seguimiento del estado de contenidos multimedia, evitando el desorden y facilitando la detección de problemas pendientes. |
| **Entidad principal (struct):** | `Content` |

### Campos del struct principal:

| Nombre del campo | Tipo de dato (C++) | Descripción / ejemplo de valor |
|---|---|---|
| `id` | `int` | Identificador único (ej: 1) |
| `contenido` | `char[100]` | Nombre del contenido (ej: "Video Institucional") |
| `tipo` | `char[30]` | Tipo: "video", "animación" o "imagen" |
| `cliente` | `char[50]` | Nombre del cliente o proyecto (ej: "UNIVALLE") |
| `fecha_entrega` | `char[15]` | Fecha en formato YYYY-MM-DD (ej: "2025-03-10") |
| `estado` | `char[30]` | Estado: "en proceso", "entregado", "pendiente de revisión" |
| `observaciones` | `char[150]` | Comentarios o problemas detectados |

---

## 3. Diseño Modular del Proyecto

El proyecto tiene una estructura diseñada para poder facilitar el mantenimiento y la escalabilidad del sistema. La estructura se organiza mediante una separación entre la gestión de contenidos, los archivos de datos binarios y las funciones de utilidad general. La función de cada módulo trabaja de manera coordinada mediante el programa principal para garantizar el flujo correcto de la información.

### 3.1 Estructura de Archivos del Proyecto

| Archivo | Tipo | Descripción del contenido |
|---|---|---|
| `main.cpp` | Programa principal | Punto de entrada; incluye cabeceras y coordina el menú principal. |
| `include/production.h` | Cabecera | Modelo `Content`, declaración de CRUD, ordenamiento y búsquedas del Grupo 10. |
| `src/production.cpp` | Implementación | Lógica principal: alta, baja, modificación, Bubble Sort, Merge Sort y Búsqueda Binaria. |
| `include/fileio.h` | Cabecera | Declaración de escritura/lectura binaria y generación de PDF/TXT. |
| `src/fileio.cpp` | Implementación | Lógica para abrir/guardar `proyectos.dat` y exportar a texto. |
| `include/utils.h` | Utilitario | Funciones auxiliares compartidas (validaciones de fecha). |
| `src/utils.cpp` | Implementación | Funciones para mostrar tablas y limpieza de datos en consola. |
| `data/proyectos.dat` | Archivo de datos | Persistencia física en formato binario. |

---

## 4. Descripción de Funciones por Módulo (Resumen)

*Se han implementado las funciones estrictas requeridas para el **Grupo 10**.*

| Función / Prototipo | Parámetros | Propósito |
|---|---|---|
| `std::pair<int, int> binarySearchByIdIterative(int id)` | `int id` (por valor) | Búsqueda binaria iterativa por ID. Retorna {índice, iteraciones}. |
| `std::pair<int, int> binarySearchByIdRecursive(int id)` | `int id` (por valor) | Búsqueda binaria recursiva por ID. Retorna {índice, llamadas}. |
| `SortStats bubbleSortByFecha(vector<Content>& arr)` | `vector& arr` (referencia) | Ordena por fecha límite usando burbuja. Retorna estadísticas. |
| `SortStats mergeSortByFecha(vector<Content>& arr)` | `vector& arr` (referencia) | Ordena por fecha límite usando intercalación. Retorna estadísticas. |
| `bool saveToBinary(const string& filename)` | `string&` (referencia constante) | Escribe el arreglo actual de `Content` en disco de forma binaria. |

---

## 5. Explicación de Algoritmos Implementados

### 5.1 Bubble Sort Optimizado
Ordena el arreglo global comparando pares adyacentes. Utiliza una variable booleana `swapped` que, si termina una vuelta entera sin hacer intercambios, rompe el ciclo prematuramente asumiendo que el arreglo ya está ordenado. Se utiliza principalmente para garantizar que las búsquedas binarias no fallen por falta de orden.

### 5.2 Búsqueda Binaria (Iterativa y Recursiva)
Se utiliza para buscar un proyecto ingresando su ID. El algoritmo comprueba el elemento del medio; si es mayor o menor, descarta toda la otra mitad del arreglo, dividiendo el problema iterativa o recursivamente. Requiere que los datos estén ordenados previamente.

### 5.3 Intercalación (Merge Sort)
Divide el arreglo en mitades sucesivas hasta tener elementos individuales, y luego los "intercala" fusionando las mitades en un nuevo arreglo temporal, siempre comparando cuál es menor para mantener el orden. En el proyecto se aplicó sobre el campo `fecha_entrega` para el reporte comparativo de eficiencia.

---

## 6. Conclusiones

**Nicole:**
> El mayor desafío fue manejar la persistencia de datos directa con archivos binarios en C++, especialmente adaptando todas las variables a tamaño fijo con arreglos de caracteres. Superé las dificultades relacionadas con el manejo de memoria. Ahora valoro cómo los archivos binarios permiten conservar la información de forma mucho más rápida y estructurada entre ejecuciones del programa.

**Carla:**
> Implementar la búsqueda binaria sobre el arreglo ordenado por ID me hizo comprender la eficiencia extrema de este algoritmo frente a la búsqueda secuencial. Aplicarlo en un contexto real me mostró que la organización de datos (ordenamiento previo) es clave para la rapidez de las consultas, algo que definitivamente aplicaré en futuros sistemas interactivos.

---

## 7. Bibliografía
[1] Deitel, P. J., & Deitel, H. M. (2000). *Cómo programar en C/C++*. Pearson Educación.  
[2] Joyanes Aguilar, L. (2010). *Fundamentos de programación: Algoritmos, estructuras de datos y objetos*. McGraw-Hill.  
