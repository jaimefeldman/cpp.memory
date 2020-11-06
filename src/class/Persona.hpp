#ifndef _PERSONA_HPP_
#define _PERSONA_HPP_

#include <string>
#include <iostream>
using namespace std;


typedef enum {MASCULINO, FEMENINO} SexoEnum;

class Persona
{
    private:
        string nombre;
        string apellido;
        unsigned int edad;
        SexoEnum sexo;
 
	public:
        Persona(string nombre, string apellido, unsigned int edad, SexoEnum sexo);
        virtual ~Persona();
        friend ostream& operator<<(ostream& stream, const Persona& item);
        const string& getNombre();
        bool operator <(const Persona& p2) const;
        const unsigned int getEdad();
        static bool ordenarPorEdadAsenente(const Persona& p1, const Persona& p2)
        {
            return (p1.edad <  p2.edad);
        }
        static bool ordenarPorEdadDesendente(const Persona& p1, const Persona& p2)
        {
            return (p1.edad > p2.edad);
        }
        const string toString();
        
};
#endif // PERSONA_HPP_
