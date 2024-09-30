#ifndef LECCION_H
#define LECCION_H

#include <string>
#include "../../ico.h"
#include "Ejercicio.h"
#include "Traduccion.h"
#include "CompletarPalabras.h"

class Leccion: public ICollectible{
    private:
        std::string Tema;
        std::string Objetivo;
        IDictionary * ejerciciosLeccion = new OrderedDictionary();
        bool aprobada;
        int orden;
        
    public:
        Leccion();
        Leccion(std::string Tema, std::string Objetivo);
        //setter & getter
        void setTema(std::string Tema);
        void setObjetivo(std::string Objetivo);
        std::string getTema();
        std::string getObjetivo();
        bool getAprobada();
        void setAprobada(bool apro);
        int getOrden();
        void setOrden(int orden);

        //
        IDictionary * getEjerciciosLeccion();
        void agregarEjercicioLeccion(Ejercicio * e);
        int getCantidadEjerciciosLeccion();
        void EliminarEjercicios();
        Ejercicio* ObtenerEjercicio(std::string descripcion);
        
};

#endif