// Archivo encargado de guardar y leer cosas en el disco duro de la computadora
#include "../include/fileio.h"
#include "../include/utils.h"
#include <fstream>
#include <iostream>

using namespace std;

namespace FileIO {

    // Guarda toda la lista de proyectos en un archivo de la computadora
    bool saveToBinary(const string& filename) {
        // Abre el archivo para escribir (y borra lo que tenía antes)
        ofstream ofs(filename, ios::binary | ios::trunc);
        if (!ofs) {
            Utils::printLine("[X] Error al abrir archivo binario para guardar.");
            return false;
        }
        // Guarda uno por uno los proyectos
        for (auto &c : Production::produccion) {
            ofs.write((char*)&c, sizeof(Content));
        }
        ofs.close(); // Cierra el archivo cuando termina
        Utils::printLine("[OK] Datos guardados en formato binario (" + to_string(Production::produccion.size()) + " registros).");
        return true;
    }

    // Lee la información que estaba guardada en el archivo de la computadora
    bool loadFromBinary(const string& filename) {
        // Abre el archivo para leer
        ifstream ifs(filename, ios::binary);
        if (!ifs) {
            Utils::printLine("[!] Archivo binario no encontrado: " + filename);
            return false;
        }
        // Limpia la lista actual antes de meter la nueva información
        Production::produccion.clear();
        Content c;
        // Lee los proyectos uno por uno y los mete a nuestra lista
        while (ifs.read((char*)&c, sizeof(Content))) {
            Production::produccion.push_back(c);
        }
        ifs.close(); // Cierra el archivo
        Utils::printLine("[OK] Datos recuperados desde binario. Registros: " + to_string(Production::produccion.size()));
        return true;
    }

    // Crea unos datos de ejemplo la primera vez que se abre el programa
    void seedData(const string& filename) {
        // Revisa si el archivo ya existe. Si existe, no hace nada.
        ifstream check(filename, ios::binary);
        if (check.is_open()) {
            check.close();
            return; 
        }
        
        // Si no existe, crea el archivo nuevo
        ofstream file(filename, ios::binary);
        if (!file) return;
        
        // Crea 10 proyectos de prueba para que la tabla no se vea vacía
        Content seed[10] = {
            {1,"VIDEO INSTITUCIONAL","VIDEO","UNIVALLE","2026-03-10","EN PROCESO","AJUSTE DE COLOR PENDIENTE"},
            {2,"ANIMACION PRODUCTO X","ANIMACION","KADILA PHARMA","2026-03-15","PENDIENTE DE REVISION","ERROR TECNICO EN AUDIO"},
            {3,"DISENO BANNER","IMAGEN","LABOMAC","2026-03-01","ENTREGADO","SIN INCONVENIENTES"},
            {4,"SPOT PROMOCIONAL","VIDEO","ACME CORP","2026-04-01","EN PROCESO","NO SE ESCUCHA"},
            {5,"GIF REDES","IMAGEN","STARTUP Y","2026-03-20","ENTREGADO","CALIDAD BAJA EN COMPRESION"},
            {6,"TUTORIAL PRODUCTO","VIDEO","UNIVALLE","2026-03-22","PENDIENTE DE REVISION","SIN INCONVENIENTES"},
            {7,"ANIMACION LOGO","ANIMACION","LABOMAC","2026-04-05","EN PROCESO","ERROR TECNICO EN AUDIO"},
            {8,"POSTER CAMPANA","IMAGEN","ACME CORP","2026-03-30","ENTREGADO","SIN INCONVENIENTES"},
            {9,"VIDEO TESTIMONIAL","VIDEO","CLIENTE Z","2026-04-10","PENDIENTE DE REVISION","NO SE ESCUCHA"},
            {10,"ANIMACION EXPLICATIVA","ANIMACION","CLIENTE A","2026-04-15","EN PROCESO","AJUSTE DE COLOR PENDIENTE"}
        };
        
        // Guarda los 10 proyectos de prueba
        for (int i = 0; i < 10; ++i) {
            file.write((char*)&seed[i], sizeof(Content));
        }
        file.close(); // Cierra el archivo
        Utils::printLine("[OK] Archivo binario creado e inicializado con 10 registros.");
    }

    // Exporta la lista de proyectos a un archivo Excel (.csv)
    bool exportToCSV(const string& filename) {
        ofstream ofs(filename);
        if (!ofs) return false;
        
        // Le dice a Excel que estamos usando letras y símbolos normales (como las tildes y las eñes)
        ofs << "\xEF\xBB\xBF";
        
        // Le avisa a Excel que vamos a separar la información usando punto y coma (;)
        ofs << "sep=;\n";

        // Escribe los títulos de las columnas
        ofs << "ID;CONTENIDO;TIPO;CLIENTE;FECHA_ENTREGA;ESTADO;OBSERVACIONES\n";
        // Escribe la información de cada proyecto en una línea separada
        for (auto &c : Production::produccion) {
            ofs << c.id << ";"
                << "\"" << c.contenido << "\";"
                << "\"" << c.tipo << "\";"
                << "\"" << c.cliente << "\";"
                << "\"" << c.fecha_entrega << "\";"
                << "\"" << c.estado << "\";"
                << "\"" << c.observaciones << "\"\n";
        }
        ofs.close(); // Termina y cierra el archivo Excel
        Utils::printLine("[OK] Reporte exportado a formato CSV para Excel: " + filename);
        return true;
    }
}
