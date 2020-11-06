#include "Persona.hpp"
#include <sstream>
#include <iostream>

using namespace std;

Persona::Persona(string nombre, string apellido, unsigned int edad, SexoEnum sexo)
{
    if(edad < 0) {
        throw invalid_argument("edad no puede ser un valor negativo");
        edad = 1;
    }
    this->nombre = nombre;
    this->apellido = apellido;
    this->edad = edad;
    this->sexo = sexo;
}
Persona::~Persona()
{
    cout << "[ Objeto persona, nombre: " << this->nombre << " ha sido destruido de la memoria.]" << endl;    
}

// descripción del objeto 
ostream& operator<<(ostream& stream, const Persona& item) {
           stream << "Nombre:   " << item.nombre     << endl
                  << "Apellido: " << item.apellido   << endl
                  << "edad:     " << item.edad       << endl
                  << "sexo:     " << (item.sexo ? "Femenino" : "Masculino");      

    return stream;
}

const string& Persona::getNombre()
{
    return this->nombre;
}


bool Persona::operator <(const Persona& p2) const
{
    return this->nombre < p2.nombre;
}

const unsigned int Persona::getEdad()
{
    return this->edad;
}

const string Persona::toString()
{
    stringstream stm;
    stm << this->nombre << " " << this->apellido 
        << ", edad: " << this->edad
        << ", sexo: " << (this->sexo ? "Femenino":"Masculino")  << endl;
    return stm.str();
}
