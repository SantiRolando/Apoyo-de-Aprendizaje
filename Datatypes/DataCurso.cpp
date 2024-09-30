#include "DataCurso.h"

//DataCurso

DataCurso::DataCurso(){}

DataCurso::DataCurso(std::string NombreCurso, std::string DescripcionCurso, TipoDificultad Dificultad, bool Habilitado){
    this->NombreCurso = NombreCurso;
    this->DescripcionCurso = DescripcionCurso;
    this->Dificultad = Dificultad;
    this->Habilitado = Habilitado;
}

DataCurso::DataCurso(std::string NombreCurso){
    this->NombreCurso = NombreCurso;
}

DataCurso::~DataCurso(){}

//getters DataCurso
std::string DataCurso::getNombreCurso(){
    return this->NombreCurso;
}

std::string DataCurso::getDescripcionCurso(){
    return this->DescripcionCurso;
}

TipoDificultad DataCurso::getDificultad(){
    return this->Dificultad;
}

bool DataCurso::getHabilitado(){
    return this->Habilitado;
}
///////////////////////////////////////////////////////////////////////////////////////

//DataCursoHab

DataCursoHab::DataCursoHab(){}

DataCursoHab::DataCursoHab(std::string NombreCurso, std::string DescripcionCurso, TipoDificultad Dificultad, bool habilitado, std::string idiomacurso, std::string profesorcurso ,IDictionary* Lecciones){
    this->NombreCurso = NombreCurso;
    this->DescripcionCurso = DescripcionCurso;
    this->Dificultad = Dificultad;
    this->Habilitado = habilitado;
    this->Lecciones = Lecciones;
    this->idiomacurso = idiomacurso;
    this->profesorcurso = profesorcurso;
}

/* DataCursoHab::~DataCursoHab(){
     for (IIterator* it = this->Lecciones->getIterator(); it->hasCurrent(); it->next()){
        OrderedKey * key = ((OrderedDictionaryEntry*)it->getCurrent())->getKey();
        Lecciones->remove(key);
    } 
} */

std::string DataCursoHab::getNombreCurso(){
    return this->NombreCurso;
}

std::string DataCursoHab::getDescripcionCurso(){
    return this->DescripcionCurso;
}

TipoDificultad DataCursoHab::getDificultad(){
    return this->Dificultad;
}

bool DataCursoHab::getHabilitado(){
    return this->Habilitado;
}

IDictionary * DataCursoHab::getLecciones(){
    if(this->Lecciones == nullptr){
        std::cout << "N/A" << std::endl;
    }
    return this->Lecciones;
}

std::string DataCursoHab::getIdiomaCurso(){
    return this->idiomacurso;
}

std::string DataCursoHab::getProfesorCurso(){
    return this->profesorcurso;
}


///////////////////////////////////////////////////////////////////////////////////////

DataCursoHabMini::DataCursoHabMini(std::string NombreCurso, std::string DescripcionCurso){
    this->NombreCurso = NombreCurso;
    this->DescripcionCurso = DescripcionCurso;
}

DataCursoHabMini::DataCursoHabMini(std::string NombreCurso){
    this->NombreCurso = NombreCurso;
}

std::string DataCursoHabMini::getNombreCurso(){
    return this->NombreCurso;
}

std::string DataCursoHabMini::getDescripcionCurso(){
    return this->DescripcionCurso;
}

bool DataCursoHabMini::getHabilitado(){
    return this->Habilitado;
}

//////////
DataEstadisticaCurso::DataEstadisticaCurso(std::string nombreCurso, double promedioAvance, std::string descripcionCurso, TipoDificultad dificultadCurso){
    this->nombreCurso  = nombreCurso;
    this->promedioAvance = promedioAvance;
    this->descripcionCurso = descripcionCurso;
    this->dificultadCurso = dificultadCurso;
}

std::string DataEstadisticaCurso::getNombreCurso(){
    return this->nombreCurso;
}
double DataEstadisticaCurso::getPromedioAvance(){
    return this->promedioAvance;
}

std::string DataEstadisticaCurso::getDescripcion(){
    return this->descripcionCurso;
}

TipoDificultad DataEstadisticaCurso::getDificultadCurso(){
    return this->dificultadCurso;
}

//////////////////infoins////////////////


InscripcionInfo::InscripcionInfo(std::string nombre, Date fecha){
    this->estudianteNombre = nombre;
    this->fechaIns = fecha;
}

std::string InscripcionInfo::getEstudianteNombre(){
    return this->estudianteNombre;
}

Date InscripcionInfo::getFechaIns(){
    return this->fechaIns;
}