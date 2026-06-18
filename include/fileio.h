#ifndef FILEIO_H
#define FILEIO_H

#include <string>
#include "production.h"

namespace FileIO {
    // Guarda la información que tenemos en el programa dentro de un archivo en la computadora (proyectos.dat)
    bool saveToBinary(const std::string& filename);
    
    // Lee la información guardada en la computadora (proyectos.dat) para usarla en el programa
    bool loadFromBinary(const std::string& filename);
    
    // Crea 10 datos de prueba automáticamente si el archivo de guardado no existe todavía
    void seedData(const std::string& filename);
    
    // Exporta o guarda toda la información en un formato especial (.csv) que se puede abrir en Excel
    bool exportToCSV(const std::string& filename);
}

#endif // FILEIO_H
