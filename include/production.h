#ifndef PRODUCTION_H
#define PRODUCTION_H

#include <string>
#include <vector>

/**
 * @struct Content
 * @brief Representa un proyecto o trabajo multimedia (video, imagen, etc.).
 * 
 * Usamos un tamaño fijo de letras (char[]) en vez de texto libre (std::string)
 * para que sea más fácil guardar esta información directamente en la computadora.
 */
struct Content {
    int id;                      // El número único que identifica a este proyecto (como su DNI)
    char contenido[100];         // El nombre o título del proyecto (ej. "Video para redes sociales")
    char tipo[30];               // Qué tipo de trabajo es: VIDEO, ANIMACION o IMAGEN
    char cliente[50];            // El nombre de la persona o empresa que pidió el trabajo
    char fecha_entrega[15];      // Para cuándo hay que entregarlo (formato Año-Mes-Día)
    char estado[30];             // Cómo va el proyecto: EN PROCESO, ENTREGADO, etc.
    char observaciones[150];     // Notas extras o comentarios sobre el trabajo
};

/**
 * @struct SortStats
 * @brief Guarda información de cuánto tardó la computadora en ordenar los datos.
 */
struct SortStats {
    long long comparisons; // Cuántas veces la computadora tuvo que comparar dos cosas
    long long swaps;       // Cuántas veces tuvo que cambiar de lugar las cosas
};

namespace Production {
    // La lista principal donde guardamos todos los proyectos mientras el programa está abierto
    extern std::vector<Content> produccion;

    // --- FUNCIONES PRINCIPALES (Crear, Leer, Actualizar, Borrar) ---
    int nextId();                              // Calcula qué número de ID le toca al siguiente proyecto nuevo
    void addContent(const Content& c);         // Guarda un nuevo proyecto en nuestra lista
    bool modifyContent(int id);                // Cambia la información de un proyecto que ya existe
    bool deleteContent(int id);                // Borra un proyecto de la lista usando su número de ID
    void showAll();                            // Muestra en la pantalla todos los proyectos ordenados

    // --- FORMAS DE ORDENAR LOS DATOS ---
    void bubbleSortByIdOptimized();            // Ordena los proyectos por su número de ID de menor a mayor
    bool isSortedById();                       // Revisa si los proyectos ya están ordenados por ID
    
    // Funciones para ordenar los proyectos por la fecha de entrega
    SortStats bubbleSortByFecha(std::vector<Content>& arr); // Un método sencillo para ordenar por fecha
    SortStats mergeSortByFecha(std::vector<Content>& arr);  // Un método más avanzado y rápido para ordenar por fecha
    void compareSortAlgorithms();                           // Compara cuál de los dos métodos de arriba fue más rápido

    // --- FORMAS DE BUSCAR UN PROYECTO ---
    std::pair<int, int> binarySearchByIdIterative(int id);  // Busca un proyecto por su ID usando un método paso a paso
    std::pair<int, int> binarySearchByIdRecursive(int id);  // Busca un proyecto por su ID usando un método que se llama a sí mismo

    // --- OTRAS HERRAMIENTAS ---
    Content makeContentFromInput();            // Le pregunta al usuario los datos para crear un proyecto nuevo
}

#endif // PRODUCTION_H
