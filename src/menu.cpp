// Archivo que controla el menú principal y todo lo que el usuario ve al inicio
#include "../include/menu.h"
#include "../include/production.h"
#include "../include/fileio.h"
#include "../include/utils.h"
#include <iostream>
#include <string>

using namespace std;

namespace Menu {

    // Escribe en la pantalla las opciones del menú para que el usuario elija
    void showMenu() {
        cout << "\n==================== PROYECTO FINAL (GRUPO 10) ====================\n";
        cout << "1. Registrar nueva entrega\n";
        cout << "2. Mostrar todas las entregas\n";
        cout << "3. Modificar entrega\n";
        cout << "4. Eliminar entrega\n";
        cout << "5. Reporte Comparativo Ordenacion (por Fecha Limite)\n";
        cout << "6. Buscar entrega por ID (Binaria Iterativa/Recursiva)\n";
        cout << "7. Generar reporte exportable (CSV)\n";
        cout << "8. Guardar datos en archivo binario\n";
        cout << "9. Recuperar datos de archivo binario\n";
        cout << "10. Salir\n";
        cout << "===================================================================\n";
        cout << "Seleccione una opcion: ";
    }

    // Esta función mantiene el programa encendido y escuchando al usuario
    void runApp() {
        string defaultFile = "data/proyectos.dat"; // Nombre del archivo donde guardamos todo
        FileIO::seedData(defaultFile); // Crea datos de prueba si el archivo no existe
        FileIO::loadFromBinary(defaultFile); // Carga los datos guardados en la computadora
        string input;
        
        // Bucle infinito: el menú se repite hasta que el usuario elija salir (opción 10)
        while (true) {
            showMenu();
            getline(cin, input); // Lee lo que el usuario escribe
            
            if (input == "1") {
                // Opción 1: Crear un nuevo proyecto
                auto c = Production::makeContentFromInput(); // Pide los datos al usuario
                Production::addContent(c); // Agrega el proyecto a la lista
                FileIO::saveToBinary(defaultFile); // Guarda los cambios en la computadora
                Utils::pause();
                
            } else if (input == "2") {
                // Opción 2: Ver todos los proyectos
                Production::showAll();
                Utils::pause();
                
            } else if (input == "3") {
                // Opción 3: Modificar un proyecto
                cout << "Ingrese ID a modificar: ";
                int id; 
                // Revisa que el usuario haya escrito un número
                if (!(cin >> id)) { cin.clear(); cin.ignore(10000,'\n'); Utils::printLine("[X] ID invalido."); Utils::pause(); continue; }
                cin.ignore(10000,'\n');
                
                // Intenta modificar. Si lo logra, guarda en la computadora
                if (!Production::modifyContent(id)) Utils::printLine("[X] No se encontro ID.");
                else FileIO::saveToBinary(defaultFile);
                Utils::pause();
                
            } else if (input == "4") {
                // Opción 4: Borrar un proyecto
                cout << "Ingrese ID a eliminar: ";
                int id; 
                // Revisa que el usuario haya escrito un número
                if (!(cin >> id)) { cin.clear(); cin.ignore(10000,'\n'); Utils::printLine("[X] ID invalido."); Utils::pause(); continue; }
                cin.ignore(10000,'\n');
                
                cout << "Confirma eliminacion (S/N): ";
                string c; getline(cin, c);
                // Si el usuario confirma con 'S' o 's', borra el proyecto
                if (c == "S" || c == "s") {
                    if (!Production::deleteContent(id)) Utils::printLine("[X] No se encontro ID.");
                    else FileIO::saveToBinary(defaultFile); // Guarda los cambios
                } else Utils::printLine("[X] Eliminacion cancelada.");
                Utils::pause();
                
            } else if (input == "5") {
                // Opción 5: Comparar formas de ordenar los proyectos
                Production::compareSortAlgorithms();
                Utils::pause();
                
            } else if (input == "6") {
                // Opción 6: Buscar un proyecto por su número (ID)
                cout << "Ingrese ID de entrega a buscar: ";
                int id; 
                if (!(cin >> id)) { cin.clear(); cin.ignore(10000,'\n'); Utils::printLine("[X] ID invalido."); Utils::pause(); continue; }
                cin.ignore(10000,'\n');
                
                cout << "Metodo: 1.Binaria Iterativa 2.Binaria Recursiva: ";
                string m; getline(cin, m);
                std::pair<int, int> res = {-1, 0};
                
                // Elige qué método de búsqueda usar
                if (m == "1") res = Production::binarySearchByIdIterative(id);
                else if (m == "2") res = Production::binarySearchByIdRecursive(id);
                else { Utils::printLine("[X] Opcion invalida."); Utils::pause(); continue; }
                
                // Muestra el resultado de la búsqueda
                if (res.first == -1) {
                    Utils::printLine("[!] No se encontro entrega. (Llamadas/Iteraciones: " + to_string(res.second) + ")");
                } else {
                    Utils::printTableHeader();
                    Utils::printContentRow(Production::produccion[res.first]);
                    Utils::printLine("[OK] Encontrado en " + to_string(res.second) + " llamadas/iteraciones.");
                }
                Utils::pause();
                
            } else if (input == "7") {
                // Opción 7: Exportar a Excel
                cout << "Generar reporte CSV. Nombre archivo (ej: reporte.csv): ";
                string out; getline(cin,out);
                if (out.empty()) out = "reporte.csv";
                // Se asegura de que el nombre del archivo termine en .csv
                if (out.length() < 4 || out.substr(out.length() - 4) != ".csv") {
                    out += ".csv";
                }
                FileIO::exportToCSV(out);
                Utils::pause();
                
            } else if (input == "8") {
                // Opción 8: Guardar a mano en la computadora
                FileIO::saveToBinary(defaultFile);
                Utils::pause();
                
            } else if (input == "9") {
                // Opción 9: Cargar a mano lo que está en la computadora
                FileIO::loadFromBinary(defaultFile);
                Utils::pause();
                
            } else if (input == "10") {
                // Opción 10: Salir del programa
                Utils::printLine("Gracias por usar el sistema. Hasta pronto!");
                break; // Rompe el bucle infinito y termina la aplicación
                
            } else {
                // Si el usuario escribe algo que no es del 1 al 10
                Utils::printLine("[X] Opcion invalida.");
                Utils::pause();
            }
        }
    }
}
