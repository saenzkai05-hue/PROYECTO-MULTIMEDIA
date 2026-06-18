#ifndef UTILS_H
#define UTILS_H

#include <string>
#include "production.h"

namespace Utils {
    // Pausa la pantalla y espera a que el usuario presione la tecla Enter para continuar
    void pause();
    
    // Escribe un mensaje en la pantalla y pasa a la siguiente línea (como presionar Enter)
    void printLine(const std::string& s);
    
    // Convierte cualquier texto a letras MAYÚSCULAS para que todo se vea igual y ordenado
    std::string toUpper(const std::string& s);
    
    // Dibuja en la pantalla la parte de arriba de una tabla (los títulos de las columnas)
    void printTableHeader();
    
    // Dibuja en la pantalla la información de un solo proyecto, como si fuera una fila de la tabla
    void printContentRow(const Content& c);
    
    // Revisa que la fecha que escribe el usuario tenga el formato correcto: Año-Mes-Día (Ej: 2024-05-20)
    bool validateDateFormat(const std::string& d);
}

#endif // UTILS_H
