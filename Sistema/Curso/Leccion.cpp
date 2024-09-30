#include "Leccion.h"

Leccion::Leccion(){}

Leccion::Leccion(std::string Tema, std::string Objetivo){
    this->Tema = Tema;
    this->Objetivo = Objetivo;
}

//setter & getter

void Leccion::setObjetivo(std::string Objetivo){
    this->Objetivo = Objetivo;
}

void Leccion::setTema(std::string Tema){
    this->Tema = Tema;
}

std::string Leccion::getObjetivo(){
    return this->Objetivo;
}

std::string Leccion::getTema(){
    return this->Tema;
}

bool Leccion::getAprobada(){
    return this->aprobada;
}

void Leccion::setAprobada(bool apro){
    this->aprobada = apro;
}
//************************************************************************************//

IDictionary * Leccion::getEjerciciosLeccion(){
    return this->ejerciciosLeccion;
}

void Leccion::agregarEjercicioLeccion(Ejercicio * e){
    OrderedKey * key = new String(e->getDescripcion().c_str());
    this->ejerciciosLeccion->add(key,e);
}

int Leccion::getCantidadEjerciciosLeccion(){
    if(this->ejerciciosLeccion != nullptr){
        return this->ejerciciosLeccion->getSize();
    }
    return 0;
}

//************************************************************************************//

//

void Leccion::EliminarEjercicios(){
    IDictionary * ejercicios = this->ejerciciosLeccion;

    IIterator * it = ejercicios->getIterator();
    while(it->hasCurrent()){
        Ejercicio * ej = dynamic_cast<Ejercicio*>(it->getCurrent());
        if(ej != nullptr){
            OrderedKey * ik = new String(ej->getDescripcion());
            ejercicios->remove(ik);
            delete ej;
        }
        it->next();
    }
    delete it;
}


Ejercicio* Leccion::ObtenerEjercicio(std::string descripcion) {
    OrderedKey* ikp = new String(descripcion);
    ICollectible* ic = this->ejerciciosLeccion->find(ikp);
    delete ikp;

    if (ic != nullptr) {
        return dynamic_cast<Ejercicio*>(ic);
    } else {
        return nullptr;
    }
}

int Leccion::getOrden(){
    return this->orden;
}

void Leccion::setOrden(int orden){
    this->orden = orden;
}