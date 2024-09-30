#include "Estudiante.h"
#include "../Curso/Curso.h"


Estudiante::Estudiante(std::string Nickname, std::string Nombre, std::string Contrasenia, std::string Descripcion, std::string Pais, Date FechaNac){
    this->Nickname = Nickname;
    this->Contrasenia = Contrasenia;
    this->Descripcion = Descripcion;
    this->Pais = Pais;
    this->FechaNac = FechaNac;
    this->Nombre = Nombre;
}

Estudiante::Estudiante(std::string Nickname, std::string Descripcion, std::string Pais, Date FechaNac){
    this->Nickname = Nickname;
    this->Descripcion = Descripcion;
    this->Pais = Pais;
    this->FechaNac = FechaNac;
}

//Operaciones Padre

void Estudiante::setNickname(std::string Nickname){
    this->Nickname = Nickname;
}

void Estudiante::setContrasenia(std::string Contrasenia){
    this->Contrasenia = Contrasenia;
}

void Estudiante::setDescripcion(std::string Descripcion){
    this->Descripcion = Descripcion;
}

std::string Estudiante::getNickname(){
    return this->Nickname;
}

std::string Estudiante::getContrasenia(){
    return this->Contrasenia;
}

std::string Estudiante::getDescripcion(){
    return this->Descripcion;
}

std::string Estudiante::getNombre(){
    return this->Nombre;
}

//Setter & getter local

void Estudiante::setPais(std::string Pais) {
    this->Pais = Pais;
}

std::string Estudiante::getPais() {
    return this->Pais;
}

void Estudiante::setFechaNac(Date FechaNac) {
    this->FechaNac = FechaNac;
}

Date Estudiante::getFechaNac() {
    return this->FechaNac;
}

//INSCRIPCION CURSO - CAMI

//Le paso el nombre del curso y se fija si pertenece a la coleccion de registros del estudiante. Si esta, es porque esta inscripto.
bool Estudiante::estaInscripto(std::string nombreCurso){
    
    OrderedKey * Ik = new String(nombreCurso);
    bool esta = false;
    if (this->registros->member(Ik))
    {
        esta = true;
    }
    return esta;
}

//Le paso el nombre de un curso y retorna si el estudiante lo aprobo (porcentaje de aprobacion == 100). 
bool Estudiante::cursoAprobado(std::string nombreCurso){

    OrderedKey * Ik = new String(nombreCurso);
    //Uso la operacion estaInscripto pero es basicamente lo mismo que poner this->registros
    if (this->registros->member(Ik))//Si nombre curso pertenece a la coleccion de registros del estudiante, esta inscripto
    {
        Registro * r = dynamic_cast<Registro*>(this->registros->find(Ik)); //Como find me devuelve un Icollectible, tengo que castear el r para poder obtener info del mismo tipo
        //Como r es un registro, puedo pedirle el porcentaje de aprobacion ya que es un atributo.
        if (r->getPorcentajeAprobacion() != 100.0)
        {
            return false;
        }else{
            return true;
        }
    }
    return false;
}

//Le paso el curso
bool Estudiante::TienePreviasAprobadas(Curso * curso){

    IDictionary * cursos_previos = new OrderedDictionary();
    //Guardo en una coleccion auxiliar, las previas del curso pasado por parametro
    cursos_previos = curso->getCursosPreviosCurso(); // Creo que se puede asignar de una sin hacer new OrderedDictionary()
    IIterator * it = cursos_previos->getIterator(); //Obtengo el iterador para poder recorrer la coleccion de previas
    while (it->hasCurrent()) //Recorro la coleccion
    {
        Curso * c = dynamic_cast<Curso*>(it->getCurrent()); //Como la coleccion que estoy recorriendo, tiene mas colecciones, tengo que castear y obtener un elemento de tipo curso
        if (!(this->cursoAprobado(c->getNombreCurso()))) //Si el estudiante no aprobo el curso, significa que no tiene la previa aprobada y retorno false.
        //Es decir, voy recorriendo todas las previas del curso, y en cada uno se verifica si el porcentaje de aprobacion es 100 (funcion que hace cursoAprobado)
        {
            return false;
        }
        it->next();
    }
    return true;
}

////


void Estudiante::agregarRegistro(std::string nombreCurso, Registro* registro){
    OrderedKey * key = new String(nombreCurso);
    this->registros->add(key, registro);
}


IDictionary * Estudiante::getCursosInscripto(){
    IDictionary * cursosInscripto = new OrderedDictionary();
    IIterator * it = this->registros->getIterator();
    while(it->hasCurrent()){
        Registro * registro = dynamic_cast<Registro*>(it->getCurrent());
        if(registro){
            Curso * curso = registro->getCurso();
            if(curso){
                OrderedKey * key = new String(curso->getNombreCurso());
                cursosInscripto->add(key,curso);
            }
        }
        it->next();
    }
    delete it;
    return cursosInscripto;
}


IDictionary * Estudiante::getCursosAprobados(){
    IDictionary * cursosaprobados = new OrderedDictionary();
    IIterator * it = this->registros->getIterator();
    while(it->hasCurrent()){
        Registro * registro = dynamic_cast<Registro*>(it->getCurrent());
        if(registro){
            Curso * curso = registro->getCurso();
            if(curso && registro->getPorcentajeAprobacion() == 100.0){
            OrderedKey * key = new String(curso->getNombreCurso());
            cursosaprobados->add(key,curso);
            }
        }
        it->next();
    }
    delete it;
    return cursosaprobados;
}

IDictionary * Estudiante::getCursosNoAprobados(){
    IDictionary * cursosaprobados = new OrderedDictionary();
    IIterator * it = this->registros->getIterator();
    while(it->hasCurrent()){
        Registro * registro = dynamic_cast<Registro*>(it->getCurrent());
        if(registro){
            Curso * curso = registro->getCurso();
            if(curso && registro->getPorcentajeAprobacion() < 100.0){
            OrderedKey * key = new String(curso->getNombreCurso());
            cursosaprobados->add(key,curso);
            }
        }
        it->next();
    }
    delete it;
    return cursosaprobados;
}

Registro * Estudiante::getRegistro(std::string nombrecurso){
    OrderedKey * key = new String(nombrecurso);
    if(this->registros->member(key)){
        Registro * registro = dynamic_cast<Registro*>(this->registros->find(key));
        return registro;
    }
    //delete key;
    return nullptr;
}

IDictionary * Estudiante::getRegistro2(){
    return this->registros;
}


void Estudiante::eliminarEstudiantedeCurso(Registro * r){
    
    IDictionary * Restudiante = this->registros; // Obtengo la coleccion de registros del estudiante
    IIterator * it = Restudiante->getIterator(); //Obtengo el iterador para recorrer la coleccion anterior

    while (it->hasCurrent()) // Itero en la coleccion
    {
        Registro * registroE = dynamic_cast<Registro*>(it->getCurrent()); //Lo casteo para obtener variable tipo registro
        //Comparo si el nombre del curso de la coleccion de registros del estudiante es igual, al nombre del curso del registro que me pasan por parametro
        if (registroE->getCurso()->getNombreCurso() == r->getCurso()->getNombreCurso()) 
        {
            //Obtengo la clave del curso para removerlo luego
            OrderedKey * Ik = new String(registroE->getCurso()->getNombreCurso());
            //Remuevo el registro de la coleccion de registros del estudiante
            Restudiante->remove(Ik);            
        }
        it->next();
    }
    delete it;  
}