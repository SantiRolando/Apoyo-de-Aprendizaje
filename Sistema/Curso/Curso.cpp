#include "Curso.h"
#include <iostream>
#include "../Usuario/Profesor.h"
#include "../Usuario/Estudiante.h"

Curso::Curso(){}

Curso::Curso(std::string NombreCurso, std::string DescripcionCurso, TipoDificultad Dificultad){
    this->NombreCurso = NombreCurso;
    this->DescripcionCurso = DescripcionCurso;
    this->Dificultad = Dificultad;
    this->Habilitado = false;
    //profesorCurso = nullptr;//asd
}

Curso::~Curso(){
IIterator * itc = this->CursosPrevios->getIterator();
    while (itc->hasCurrent())
    {
        ICollectible * cp = itc->getCurrent();
        delete cp;
        itc->next();
    }
    delete itc;
    delete this->CursosPrevios;

    IIterator * itl = this->leccionesCurso->getIterator();
    while (itl->hasCurrent())
    {
        ICollectible * lecciones = itl->getCurrent();
        delete lecciones;
        itl->next();
    }
    delete itl;
    delete this->leccionesCurso;

    IIterator * ite = this->estudiantesCurso->getIterator();
    while (ite->hasCurrent())
    {
        ICollectible * estudiantes = ite->getCurrent();
        delete estudiantes;
        ite->next();
    }
    delete ite;
    delete this->estudiantesCurso;

   IIterator * itr = this->registrosInscripcion->getIterator();
   while (itr->hasCurrent())
   {
    ICollectible * registros = itr->getCurrent();
    delete registros;
    itr->next();
   }
   delete itr;
   delete this->registrosInscripcion;
}


//setters & getters

void Curso::setNombreCurso(std::string NombreCurso){
    this->NombreCurso = NombreCurso;
}

void Curso::setDescripcionCurso(std::string DescripcionCurso){
    this->DescripcionCurso = DescripcionCurso;
}

void Curso::setDificultad(TipoDificultad Dificultad){
    this->Dificultad = Dificultad;
}

void Curso::setHabilitado(bool Habilitado){
    this->Habilitado = Habilitado;
}

std::string Curso::getNombreCurso(){
    return this->NombreCurso;
}

std::string Curso::getDescripcionCurso(){
    return this->DescripcionCurso;
}

TipoDificultad Curso::getDificultad(){
    return this->Dificultad;
}

bool Curso::getHabilitado(){
    return this->Habilitado;
}

//idioma

void Curso::setIdioma(Idioma * idiomaCurso){
    this->idiomaCurso = idiomaCurso;
}

//************************************************************************************//

void Curso::AgregarIdiomaCurso(Idioma * i){
    this->idiomaCurso = i;
}

std::string Curso::GetIdiomaCurso(){
    if(idiomaCurso == nullptr){
        std::cout << "N/A" << std::endl;
    }else{
        return this->idiomaCurso->getNombreIdioma();
    }
    
}

//************************************************************************************//

 void Curso::setProfesorCurso(Profesor * p){
    this->profesorCurso = p;
}

std::string Curso::getProfesorCurso(){
    if(profesorCurso == nullptr){
        std::cout << "Profesor no asignado al curso" << std::endl;
    }
    return this->profesorCurso->getNickname();
}

//************************************************************************************//
        
IDictionary * Curso::getLecciones(){
    if(leccionesCurso == nullptr){
        std::cout << "N/A" << std::endl;
    }else{
        return this->leccionesCurso;
    }
}

void Curso::AgregarLeccionCurso(Leccion * l){
    static int orden = 0;
    l->setOrden(orden++);
    OrderedKey * key = new String(l->getTema().c_str());
    this->leccionesCurso->add(key,l);
}

//************************************************************************************//

void Curso::AgregarCursoPrevioCurso(Curso * c){
    OrderedKey * key = new String(c->getNombreCurso().c_str());
    this->CursosPrevios->add(key,c);
}

IDictionary * Curso::getCursosPreviosCurso(){
    if(CursosPrevios == nullptr){
        std::cout << "N/A" << std::endl;
        return nullptr;
    }else{
        return this->CursosPrevios;
    }
}

bool Curso::TieneLeccionConEjercicios(){
    IIterator * it = this->leccionesCurso->getIterator();
    while(it->hasCurrent()){
        Leccion * leccion = dynamic_cast<Leccion*>(it->getCurrent());
        if(leccion == nullptr && leccion->getEjerciciosLeccion()->isEmpty()){
            std::cout << "El curso no tiene leccion ni ejercicios" << std::endl;
            return false;
        } 
        if(leccion != nullptr && leccion->getEjerciciosLeccion()->isEmpty()){
            std::cout << "El curso tiene leccion pero no tiene ejercicios" << std::endl;
            return false;
        }
    it->next();
    }
    
    delete it;
    return true;
}

//************************************************************************************//
//estudiante (inscribir a curso)

void Curso::agregarEstudiante(Estudiante * e){
    OrderedKey * key = new String(e->getNickname().c_str());
    this->estudiantesCurso->add(key,e);
}

int Curso::getCantidadLecciones(){
    if(this->leccionesCurso != nullptr){
        return this->leccionesCurso->getSize();
    }
    return 0;
}

//Eliminar curso


void Curso::agregarRegistroInscripcion(Registro * registro){
    OrderedKey* key = new String(registro->getEstudiante()->getNickname());
    this->registrosInscripcion->add(key, registro);
}


int Curso::getTotalEejercicios(){
     int totalEjercicios = 0;
    IIterator* it = this->leccionesCurso->getIterator();
    
    while (it->hasCurrent()) {
        Leccion* leccion = dynamic_cast<Leccion*>(it->getCurrent());
        if (leccion != nullptr) {
            totalEjercicios += leccion->getCantidadEjerciciosLeccion();
        }
        it->next();
    }
    
    delete it;
    return totalEjercicios;
}

IDictionary * Curso::getRegistroInscripcion(){
    return this->registrosInscripcion;
}


//12

Leccion* Curso::ultimaLeccionNoAprobada(Estudiante *estudiante, std::string nombrecurso) {
    Registro * registro = dynamic_cast<Registro*>(estudiante->getRegistro(nombrecurso));
    if(!registro){
        return nullptr;
    }

    IIterator * it = this->leccionesCurso->getInverseIterator();

    while (it->hasCurrent()) {
        Leccion * leccion = dynamic_cast<Leccion *>(it->getCurrent());
        if (leccion && !registro->esLeccionAprobada(leccion->getTema())) { // !leccion->getAprobada()&& !registro->esLeccionAprobada(leccion->getTema()
            delete it;
            return leccion; 
        }
        it->next();
    }

    delete it;
    return nullptr; 
}

IDictionary * Curso::getEst(){
    return this->estudiantesCurso;
}


void Curso::EliminarLecciones(){
    IDictionary * lecciones = this->leccionesCurso;
    IIterator * it = lecciones->getIterator();
    while(it->hasCurrent()){
        Leccion * leccion = dynamic_cast<Leccion*>(it->getCurrent());
        OrderedKey * ik = new String(leccion->getTema());
        leccion->EliminarEjercicios();
        lecciones->remove(ik);
        delete leccion;
        it->next();
    }
    delete it;
}

Leccion* Curso::ObtenerLeccion(std::string tema){
    OrderedKey* ikp = new String(tema);
    ICollectible* ic = this->leccionesCurso->find(ikp);
    delete ikp;

    if (ic != nullptr) {
        return dynamic_cast<Leccion*>(ic);
    } else {
        return nullptr;
    }
}


//Agregadas correccion
