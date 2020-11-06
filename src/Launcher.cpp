/********************************************************************\
 * Launcher.cpp: 
 *      Punto de inicio para las app de c++ 
 * 
 * Comentario:
 *      Aprendiendo acerca del manejo de memoria en c++
 *      primero vermos un poco el patron RAII ("resource acquisition 
 *      is initialization") que podría traducirse como adquirir recursos
 *      es inicializar.
 *      esto se implementa por la necisdad que de que cuando se lanza 
 *      una exeption. se ve interupido el flujo normal del codigo en 
 *      busca de su catch y muchas veces no se ejecuta el delete 
 *      y se crea un leak o fuga de memoria.
 *      La comprobación de fugas de memoria en macos se realiza
 *      con con el comando leaks:
 *          $leaks -atExit -- ./bin/ejecutable
 *      o para ver solo una linea 
 *          $leaks -atExit -- ./bin/ejecutable | grep LEAK:
 *      
 *      en linux se usa el comando valgrind
 *
 * Author  : Jaime Feldman B. 2020
 * Licence : GPLv3
\********************************************************************/

#include <iostream>
#include "Persona.hpp"

using namespace std;

struct Persona_t {
    Persona_t(string nombre, string apellido, unsigned int edad, SexoEnum sexo)
        :persona(new Persona(nombre, apellido, edad, sexo)) {}
    ~Persona_t() { delete persona; }

    string getNombre() { return persona->getNombre(); }
   
    Persona *persona = { nullptr };
};

void run(void) {
   
    cout << "Creando un objeto persoan:" << endl;
    //Persona *persona = new Persona("Jaime", "Feldman", 45, MASCULINO);
    Persona_t persona("Jaime", "Feldman", 45, MASCULINO);

    cout << "nombre del objeto persona: " << persona.getNombre() << endl;

    throw "Lanzando una exception!";
    
    //delete persona;

    
}


int main(int argc, char *argv[])
{
       try {
            run();
       } catch(...) {
            cout << "capturando la excepción!" << endl;
       }
       return 0;
}
