// Archivos que manejan la lógica del programa
#include <cstring>
#include "../include/production.h"
#include "../include/utils.h"
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cctype>

using namespace std;

namespace Production {
    // La lista principal donde guardamos los proyectos mientras el programa se ejecuta
    vector<Content> produccion;

    // Calcula qué número de ID le toca a un proyecto nuevo
    int nextId() {
        if (produccion.empty()) return 1; // Si no hay nada, empieza en 1
        int maxId = 0;
        // Busca cuál es el ID más grande actualmente y le suma 1
        for (auto &c : produccion) if (c.id > maxId) maxId = c.id;
        return maxId + 1;
    }

    // Agrega un proyecto nuevo a nuestra lista
    void addContent(const Content& c) {
        produccion.push_back(c);
        Utils::printLine("[OK] Entrega registrada exitosamente con ID " + to_string(c.id));
    }

    // Cambia la información de un proyecto
    bool modifyContent(int id) {
        for (auto &item : produccion) {
            if (item.id == id) { // Encuentra el proyecto con el ID buscado
                Utils::printLine("Modificando ID " + to_string(id) + " (Enter para mantener actual)");
                
                string s;
                // Pide los nuevos datos. Si el usuario solo presiona Enter, se queda con el dato viejo.
                cout << "Nombre [" << item.contenido << "]: ";
                getline(cin, s); if (!s.empty()) { strncpy(item.contenido, (Utils::toUpper(s)).c_str(), sizeof(item.contenido)-1); item.contenido[sizeof(item.contenido)-1] = '\0'; }

                cout << "Tipo (VIDEO/ANIMACION/IMAGEN) [" << item.tipo << "]: ";
                getline(cin, s);
                if (!s.empty()) {
                    string upper = Utils::toUpper(s);
                    if (upper == "VIDEO" || upper == "ANIMACION" || upper == "IMAGEN") {
                        strncpy(item.tipo, (upper).c_str(), sizeof(item.tipo)-1); item.tipo[sizeof(item.tipo)-1] = '\0';
                    } else Utils::printLine("[!] Tipo invalido, se mantiene el anterior.");
                }

                cout << "Cliente [" << item.cliente << "]: ";
                getline(cin, s); if (!s.empty()) { strncpy(item.cliente, (Utils::toUpper(s)).c_str(), sizeof(item.cliente)-1); item.cliente[sizeof(item.cliente)-1] = '\0'; }

                cout << "Fecha entrega (YYYY-MM-DD) [" << item.fecha_entrega << "]: ";
                getline(cin, s);
                if (!s.empty()) {
                    if (Utils::validateDateFormat(s)) {
                        strncpy(item.fecha_entrega, (s).c_str(), sizeof(item.fecha_entrega)-1); item.fecha_entrega[sizeof(item.fecha_entrega)-1] = '\0';
                    } else Utils::printLine("[!] Formato de fecha invalido, se mantiene el anterior.");
                }

                cout << "Estado (EN PROCESO/ENTREGADO/PENDIENTE DE REVISION) [" << item.estado << "]: ";
                getline(cin, s);
                if (!s.empty()) {
                    string upper = Utils::toUpper(s);
                    if (upper == "EN PROCESO" || upper == "ENTREGADO" || upper == "PENDIENTE DE REVISION") {
                        strncpy(item.estado, (upper).c_str(), sizeof(item.estado)-1); item.estado[sizeof(item.estado)-1] = '\0';
                    } else Utils::printLine("[!] Estado invalido, se mantiene el anterior.");
                }

                cout << "Observaciones [" << item.observaciones << "]: ";
                getline(cin, s); if (!s.empty()) { strncpy(item.observaciones, (Utils::toUpper(s)).c_str(), sizeof(item.observaciones)-1); item.observaciones[sizeof(item.observaciones)-1] = '\0'; }

                Utils::printLine("[OK] Entrega modificada.");
                return true; // Terminó de modificar con éxito
            }
        }
        return false; // No encontró el ID
    }

    // Borra un proyecto de la lista
    bool deleteContent(int id) {
        for (auto it = produccion.begin(); it != produccion.end(); ++it) {
            if (it->id == id) {
                produccion.erase(it); // Lo elimina
                Utils::printLine("[OK] Entrega eliminada.");
                return true;
            }
        }
        return false;
    }

    // Muestra todos los proyectos en la pantalla
    void showAll() {
        if (produccion.empty()) {
            Utils::printLine("[!] No hay entregas registradas.");
            return;
        }
        
        // Primero los ordena por fecha de entrega usando el método más rápido
        mergeSortByFecha(produccion);

        Utils::printTableHeader();
        for (auto &c : produccion) Utils::printContentRow(c); // Dibuja la fila de cada uno
        Utils::printLine("Total: " + to_string(produccion.size()) + " registros. (Ordenados cronologicamente)");
    }

    // Un método sencillo para ordenar los proyectos por su ID (Bubble Sort)
    void bubbleSortByIdOptimized() {
        bool swapped;
        size_t n = produccion.size();
        for (size_t i = 0; i < n; ++i) {
            swapped = false;
            for (size_t j = 0; j + 1 < n - i; ++j) {
                // Si el de la izquierda es mayor que el de la derecha, los intercambia
                if (produccion[j].id > produccion[j+1].id) {
                    swap(produccion[j], produccion[j+1]);
                    swapped = true;
                }
            }
            if (!swapped) break; // Si no intercambió nada, ya está ordenado
        }
        Utils::printLine("[OK] Ordenamiento interno por ID completado.");
    }

    // Método sencillo para ordenar por fecha de entrega y contar cuánto tarda (para la competencia)
    SortStats bubbleSortByFecha(vector<Content>& arr) {
        SortStats stats = {0, 0};
        bool swapped;
        size_t n = arr.size();
        for (size_t i = 0; i < n; ++i) {
            swapped = false;
            for (size_t j = 0; j + 1 < n - i; ++j) {
                stats.comparisons++;
                // Compara las fechas como si fueran texto
                if (string(arr[j].fecha_entrega) > string(arr[j+1].fecha_entrega)) {
                    swap(arr[j], arr[j+1]);
                    stats.swaps++;
                    swapped = true;
                }
            }
            if (!swapped) break;
        }
        return stats;
    }

    // Función auxiliar para el método avanzado de ordenar (Merge Sort)
    // Su trabajo es unir dos listas que ya están ordenadas en una sola
    void merge(vector<Content>& arr, int left, int mid, int right, SortStats& stats) {
        int n1 = mid - left + 1;
        int n2 = right - mid;
        vector<Content> L(n1), R(n2);
        for (int i = 0; i < n1; i++) L[i] = arr[left + i];
        for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];
        
        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2) {
            stats.comparisons++;
            if (string(L[i].fecha_entrega) <= string(R[j].fecha_entrega)) {
                arr[k] = L[i];
                i++;
            } else {
                arr[k] = R[j];
                j++;
            }
            stats.swaps++;
            k++;
        }
        while (i < n1) { arr[k] = L[i]; i++; k++; stats.swaps++; }
        while (j < n2) { arr[k] = R[j]; j++; k++; stats.swaps++; }
    }

    // El método avanzado para ordenar partiendo la lista a la mitad repetidamente
    void mergeSort(vector<Content>& arr, int left, int right, SortStats& stats) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSort(arr, left, mid, stats); // Ordena la mitad izquierda
            mergeSort(arr, mid + 1, right, stats); // Ordena la mitad derecha
            merge(arr, left, mid, right, stats); // Une ambas mitades
        }
    }

    // Prepara todo para usar el método avanzado y cuenta cuánto tarda
    SortStats mergeSortByFecha(vector<Content>& arr) {
        SortStats stats = {0, 0};
        if(!arr.empty()) {
            mergeSort(arr, 0, arr.size() - 1, stats);
        }
        return stats;
    }

    // Compara el método sencillo con el avanzado para ver cuál es mejor
    void compareSortAlgorithms() {
        if (produccion.empty()) {
            Utils::printLine("[!] No hay datos para ordenar.");
            return;
        }
        // Crea dos copias de la lista para que la competencia sea justa
        vector<Content> copy1 = produccion;
        vector<Content> copy2 = produccion;
        
        SortStats statsBubble = bubbleSortByFecha(copy1);
        SortStats statsMerge = mergeSortByFecha(copy2);
        
        // Muestra los resultados en una tabla
        Utils::printLine("\n--- REPORTE COMPARATIVO DE ORDENACION (POR FECHA LIMITE) ---");
        Utils::printLine("Algoritmo            | Comparaciones | Intercambios/Mov.");
        Utils::printLine("---------------------|---------------|------------------");
        cout << left << setw(21) << "Bubble Sort (Opt)" << "| " 
             << setw(14) << statsBubble.comparisons << "| " 
             << statsBubble.swaps << "\n";
        cout << left << setw(21) << "Intercalacion (Merge)" << "| " 
             << setw(14) << statsMerge.comparisons << "| " 
             << statsMerge.swaps << "\n";
        Utils::printLine("------------------------------------------------------");
        
        // Decide cuál ganó sumando comparaciones y movimientos
        if ((statsMerge.comparisons + statsMerge.swaps) < (statsBubble.comparisons + statsBubble.swaps)) {
            Utils::printLine("CONCLUSION: Intercalacion (Merge Sort) fue mas eficiente.");
        } else {
            Utils::printLine("CONCLUSION: Bubble Sort (Opt) fue mas eficiente.");
        }
        
        produccion = copy2; 
        Utils::printLine("[OK] Los datos ahora estan ordenados por fecha limite.");
    }

    // Revisa si los proyectos están ordenados de menor a mayor ID
    bool isSortedById() {
        for (size_t i = 1; i < produccion.size(); ++i)
            if (produccion[i-1].id > produccion[i].id) return false;
        return true;
    }

    // Busca un ID rápidamente partiendo la lista a la mitad (paso a paso con un ciclo)
    std::pair<int, int> binarySearchByIdIterative(int id) {
        if (!isSortedById()) {
            Utils::printLine("[!] El arreglo no está ordenado por ID. Ejecutando ordenamiento automático.");
            bubbleSortByIdOptimized(); // Esta búsqueda solo funciona si la lista está ordenada
        }
        int left = 0, right = (int)produccion.size() - 1;
        int iter = 0; // Para contar cuántos pasos dio
        while (left <= right) {
            iter++;
            int mid = left + (right - left) / 2;
            if (produccion[mid].id == id) return {mid, iter}; // Lo encontró
            if (produccion[mid].id < id) left = mid + 1; // Busca en la mitad derecha
            else right = mid - 1; // Busca en la mitad izquierda
        }
        return {-1, iter}; // No lo encontró
    }

    // Función auxiliar para buscar partiendo a la mitad llamándose a sí misma (recursividad)
    std::pair<int, int> binarySearchByIdRecursiveHelper(int id, int left, int right, int calls) {
        if (left > right) return {-1, calls};
        int mid = left + (right - left) / 2;
        if (produccion[mid].id == id) return {mid, calls};
        if (produccion[mid].id < id) return binarySearchByIdRecursiveHelper(id, mid + 1, right, calls + 1);
        return binarySearchByIdRecursiveHelper(id, left, mid - 1, calls + 1);
    }

    // Busca un ID rápidamente partiendo a la mitad (recursividad)
    std::pair<int, int> binarySearchByIdRecursive(int id) {
        if (!isSortedById()) {
            Utils::printLine("[!] El arreglo no está ordenado por ID. Ejecutando ordenamiento automático.");
            bubbleSortByIdOptimized();
        }
        return binarySearchByIdRecursiveHelper(id, 0, (int)produccion.size() - 1, 1);
    }

    // Hace una serie de preguntas al usuario para crear un proyecto nuevo
    Content makeContentFromInput() {
        Content c;
        c.id = nextId(); // Le da un número único automáticamente
        string s;
        cout << "Nombre del contenido: "; getline(cin, s); strncpy(c.contenido, (Utils::toUpper(s)).c_str(), sizeof(c.contenido)-1); c.contenido[sizeof(c.contenido)-1] = '\0';

        // Sigue preguntando hasta que el usuario escriba un tipo válido
        while (true) {
            cout << "Tipo (VIDEO/ANIMACION/IMAGEN): "; getline(cin, s);
            string upper = Utils::toUpper(s);
            if (upper == "VIDEO" || upper == "ANIMACION" || upper == "IMAGEN") { strncpy(c.tipo, (upper).c_str(), sizeof(c.tipo)-1); c.tipo[sizeof(c.tipo)-1] = '\0'; break; }
            Utils::printLine("[X] Tipo invalido. Opciones: VIDEO, ANIMACION, IMAGEN.");
        }

        cout << "Cliente o proyecto: "; getline(cin, s); strncpy(c.cliente, (Utils::toUpper(s)).c_str(), sizeof(c.cliente)-1); c.cliente[sizeof(c.cliente)-1] = '\0';

        // Sigue preguntando hasta que la fecha tenga el formato correcto
        while (true) {
            cout << "Fecha limite de entrega (YYYY-MM-DD): "; getline(cin, s);
            if (Utils::validateDateFormat(s)) { strncpy(c.fecha_entrega, (s).c_str(), sizeof(c.fecha_entrega)-1); c.fecha_entrega[sizeof(c.fecha_entrega)-1] = '\0'; break; }
            Utils::printLine("[X] Formato invalido. Use YYYY-MM-DD (ej: 2025-04-15).");
        }

        // Sigue preguntando hasta que el estado sea válido
        while (true) {
            cout << "Estado (EN PROCESO/ENTREGADO/PENDIENTE DE REVISION): "; getline(cin, s);
            string upper = Utils::toUpper(s);
            if (upper == "EN PROCESO" || upper == "ENTREGADO" || upper == "PENDIENTE DE REVISION") { strncpy(c.estado, (upper).c_str(), sizeof(c.estado)-1); c.estado[sizeof(c.estado)-1] = '\0'; break; }
            Utils::printLine("[X] Estado invalido. Opciones: EN PROCESO, ENTREGADO, PENDIENTE DE REVISION.");
        }

        cout << "Observaciones: "; getline(cin, s); strncpy(c.observaciones, (Utils::toUpper(s)).c_str(), sizeof(c.observaciones)-1); c.observaciones[sizeof(c.observaciones)-1] = '\0';
        return c; // Retorna el proyecto con todos sus datos completos
    }
}
