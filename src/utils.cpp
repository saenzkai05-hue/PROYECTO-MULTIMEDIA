// Archivo de utilidades: cosas pequeñas que ayudan a que todo funcione mejor
#include "../include/utils.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <regex>
#include <limits>

using namespace std;

namespace Utils {
    // Hace que la pantalla se detenga hasta que el usuario presione Enter
    void pause() {
        cout << "\nPresione Enter para continuar...";
        string dummy;
        getline(cin, dummy); // Espera a que el usuario escriba algo y presione Enter
    }

    // Escribe un mensaje en la pantalla y pasa al siguiente renglón
    void printLine(const string& s) {
        cout << s << "\n";
    }

    // Toma cualquier palabra o frase y la convierte a MAYÚSCULAS
    string toUpper(const string& s) {
        string r = s;
        // Pasa por cada letra y la hace mayúscula
        transform(r.begin(), r.end(), r.begin(), [](unsigned char c){ return toupper(c); });
        return r;
    }

    // Dibuja la parte de arriba de una tabla bonita para mostrar los datos
    void printTableHeader() {
        cout << "+" << string(147, '-') << "+\n"; // Línea separadora
        cout << left 
             << "| " << setw(4) << "ID" 
             << "| " << setw(25) << "CONTENIDO" 
             << "| " << setw(12) << "TIPO" 
             << "| " << setw(20) << "CLIENTE" 
             << "| " << setw(12) << "FECHA" 
             << "| " << setw(25) << "ESTADO" 
             << "| " << setw(35) << "OBSERVACIONES" << "|\n";
        cout << "+" << string(147, '-') << "+\n"; // Línea separadora
    }

    // Escribe la información de un solo proyecto en la tabla
    void printContentRow(const Content& c) {
        cout << left 
             << "| " << setw(4) << c.id 
             << "| " << setw(25) << string(c.contenido).substr(0, 24) 
             << "| " << setw(12) << string(c.tipo).substr(0, 11) 
             << "| " << setw(20) << string(c.cliente).substr(0, 19) 
             << "| " << setw(12) << string(c.fecha_entrega).substr(0, 11) 
             << "| " << setw(25) << string(c.estado).substr(0, 24) 
             << "| " << setw(35) << string(c.observaciones).substr(0, 34) << "|\n";
    }

    // Revisa que la fecha escrita por el usuario tenga la forma Año-Mes-Día
    bool validateDateFormat(const string& d) {
        // Usamos una regla especial (regex) para ver si la fecha son 4 números, un guion, 2 números, un guion, y 2 números
        regex r("^\\d{4}-\\d{2}-\\d{2}$");
        return regex_match(d, r);
    }
}
