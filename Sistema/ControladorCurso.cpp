#include "ControladorCurso.h"

ControladorCurso *ControladorCurso::instance = nullptr;

ControladorCurso::ControladorCurso()
{
    this->cursos = new OrderedDictionary();
}

ControladorCurso *ControladorCurso::getInstance()
{
    if (instance == nullptr)
    {
        instance = new ControladorCurso();
    }
    return instance;
}

ControladorUsuario *Cuser = ControladorUsuario::getInstance();

static HandlerIdioma *idiomashandler = HandlerIdioma::getInstance();

//************************************************************************************//
// AltaCurso

IDictionary *ControladorCurso::IngresarCurso(std::string nicknamep, std::string nombrec, std::string descripcionc, TipoDificultad dificultadc)
{
    OrderedKey *ikey = new String(nombrec);
    IDictionary *auxlist;
    ICollectible *ic = Cuser->ObtenerProfesor(nicknamep);
    Profesor *pa = Cuser->ObtenerProfesor(nicknamep);

    if (this->cursos->member(ikey))
    {
        std::cout << "Ya existe este curso" << std::endl;
        return nullptr;
    }
    else
    {
        Curso *c = new Curso(nombrec, descripcionc, dificultadc);
        c->setProfesorCurso(pa);
        this->cursos->add(ikey, c);
        if (pa != nullptr)
        {
            pa->AgregarCursoProfesor(c);
        }
        // delete ikey;
        std::cout << "Curso ingresado exitosamente" << std::endl;
    }

    if (ic != nullptr)
    {
        Profesor *p = dynamic_cast<Profesor *>(ic);
        if (p != nullptr)
        {
            auxlist = p->getIdiomasProfesor();
        }
        else
        {
            std::cout << "Profesor no valido" << std::endl;
            return nullptr;
        }
    }
    else
    {
        std::cout << "No se encontre al profesor con el nickname seleccionado" << std::endl;
        return nullptr;
    }

    // delete ikey;
    return auxlist;
}

void ControladorCurso::AgregarIdiomaCurso(std::string nombreidioma)
{

    Idioma *idioma = idiomashandler->ObtenerIdiomaPorNombre(nombreidioma);
    if (idioma != nullptr)
    {
        bool profTieneIdioma = Cuser->IdiomaPerteneceAProfesor(cursoActual->getProfesorCurso(), nombreidioma);
        if (profTieneIdioma)
        {
            cursoActual->AgregarIdiomaCurso(idioma);
            std::cout << "El idioma ha sido asignado correctamente al curso" << std::endl;
        }
        else
        {
            std::cout << "El idioma ingresado no pertenece a la lista de idiomas del profesor" << std::endl;
        }
    }
    else
    {
        std::cout << "No se encontro el idioma con nombre: " << nombreidioma << std::endl;
    }
}

IDictionary *ControladorCurso::ListarCursosHabilitados()
{
    IIterator *itc = this->cursos->getIterator();
    IDictionary *cursoshabilitados = new OrderedDictionary();

    while (itc->hasCurrent())
    {
        Curso *curso = dynamic_cast<Curso *>(itc->getCurrent());
        if (curso->getHabilitado() == true)
        {
            DataCursoHabMini *dataCurso = new DataCursoHabMini(curso->getNombreCurso());
            OrderedKey *key = new String(curso->getNombreCurso().c_str());
            cursoshabilitados->add(key, dataCurso);
        }
        itc->next();
    }
    delete itc;
    return cursoshabilitados;
}

IDictionary *ControladorCurso::ListarCursosHabilitadosAprobados(std::string nickname)
{

    Estudiante *estudiante = Cuser->ObtenerEstudiante(nickname);

    IIterator *itc = this->cursos->getIterator();
    IDictionary *cursoshabilitados = new OrderedDictionary();

    while (itc->hasCurrent())
    {
        Curso *curso = dynamic_cast<Curso *>(itc->getCurrent());
        if (curso->getHabilitado() == true)
        {
            Registro *registro = dynamic_cast<Registro *>(estudiante->getRegistro(curso->getNombreCurso()));
            if (registro && registro->getPorcentajeAprobacion() == 100.0)
            {
                DataCursoHabMini *dataCurso = new DataCursoHabMini(curso->getNombreCurso());
                OrderedKey *key = new String(curso->getNombreCurso().c_str());
                cursoshabilitados->add(key, dataCurso);
            }
        }
        itc->next();
    }
    delete itc;
    return cursoshabilitados;
}

void ControladorCurso::AgregarCursoPrevio(std::string nombrecurso)
{
    IKey *ikey = new String(nombrecurso);

    if (this->cursos->member(ikey))
    {
        ICollectible *ic = this->cursos->find(ikey);
        Curso *curso = dynamic_cast<Curso *>(ic);
        if (curso != nullptr)
        {
            this->cursoActual->AgregarCursoPrevioCurso(curso);
            std::cout << "El curso ha sido asignado correctamente como curso previo" << std::endl;
        }
        else
        {
            std::cout << "Error en el dynamic_cast" << std::endl;
        }
    }
    else
    {
        std::cout << std::endl;
        std::cout << "Curso ingresado no existe" << std::endl;
        std::cout << std::endl;
    }
    delete ikey;
}

//************************************************************************************//
// 6 - Agregar Leccion

void ControladorCurso::AgregarLeccion(std::string tema, std::string objetivo, std::string nombrecurso)
{
    OrderedKey *key = new String(nombrecurso);

    if (this->cursos->member(key))//se fija si existe el nombre curso en la coleccion de cursos
    {
        Curso *curso = dynamic_cast<Curso *>(this->cursos->find(key));//busca ese curso para con el puntero curso apuntarlo
        if (curso != nullptr)
        {
            Leccion *leccion = new Leccion(tema, objetivo);//Genera una nueva leccion porque existe ese curso
            curso->AgregarLeccionCurso(leccion);//le añade a ese curso que existe la leccion pasandole por puntero la nueva leccion que le va a agregas
            std::cout << "Leccion agregada correctamente al curso " << curso->getNombreCurso() << std::endl;
        }
        else
        {
            std::cout << "Error al obtener el curso" << std::endl;
        }
    }
    else
    {
        std::cout << "No existe un curso con el nombre " << nombrecurso << std::endl;
    }

    delete key;
}

//************************************************************************************//
// 7 - Agregar Ejercicio

void ControladorCurso::AgregarEjercicioTraduccion(std::string nombrecurso, std::string temaleccion, std::string frase, std::string descripcion, std::string fraseCorrectaT)
{
    OrderedKey *key = new String(nombrecurso);
    if (this->cursos->member(key))
    {
        Curso *curso = dynamic_cast<Curso *>(this->cursos->find(key));
        if (curso != nullptr)
        {
            IDictionary *lecciones = curso->getLecciones();
            IIterator *it = lecciones->getIterator();
            while (it->hasCurrent())
            {
                Leccion *leccion = dynamic_cast<Leccion *>(it->getCurrent());
                if (leccion != nullptr && leccion->getTema() == temaleccion)
                {
                    Ejercicio *ejercicio = new Traduccion(ejerciciosContador++, frase, descripcion, fraseCorrectaT);
                    leccion->agregarEjercicioLeccion(ejercicio);
                    std::cout << "Ejercicio de traduccion agregado correctamente" << std::endl;
                }
                it->next();
            }
            delete it;
        }
        else
        {
            std::cout << "Error al obtener curso" << std::endl;
        }
    }
    else
    {
        std::cout << "No existe curso con nombre " << nombrecurso << std::endl;
    }
    delete key;
}

void ControladorCurso::AgregarEjercicioCompletarPalabras(std::string nombrecurso, std::string temaleccion, std::string frase, std::string descripcion, std::string palabras)
{
    OrderedKey *key = new String(nombrecurso);
    if (this->cursos->member(key))
    {
        Curso *curso = dynamic_cast<Curso *>(this->cursos->find(key));
        if (curso != nullptr)
        {
            IDictionary *lecciones = curso->getLecciones();
            IIterator *it = lecciones->getIterator();
            while (it->hasCurrent())
            {
                Leccion *leccion = dynamic_cast<Leccion *>(it->getCurrent());
                if (leccion != nullptr && leccion->getTema() == temaleccion)
                {
                    Ejercicio *ejercicio = new CompletarPalabras(ejerciciosContador++, frase, descripcion, palabras);
                    leccion->agregarEjercicioLeccion(ejercicio);
                    std::cout << "Ejericicio de completar palabras agregado correctamente" << std::endl;
                }
                it->next();
            }
            delete it;
        }
        else
        {
            std::cout << "Error al obtener curso" << std::endl;
        }
    }
    else
    {
        std::cout << "No existe curso con nombre " << nombrecurso << std::endl;
    }
    delete key;
}

bool ControladorCurso::ExisteLeccion(std::string nombrecurso, std::string tema)
{
    OrderedKey *key = new String(nombrecurso);
    if (this->cursos->member(key))
    {
        Curso *curso = dynamic_cast<Curso *>(this->cursos->find(key));
        if (curso != nullptr)
        {
            IDictionary *lecciones = curso->getLecciones();
            IIterator *it = lecciones->getIterator();
            while (it->hasCurrent())
            {
                Leccion *leccion = dynamic_cast<Leccion *>(it->getCurrent());
                if (leccion != nullptr && leccion->getTema() == tema)
                {
                    delete it;
                    return true;
                }
                it->next();
            }
            delete it;
        }
    }
    // delete key;
    return false;
}

//************************************************************************************//
// 8 - HabilitarCurso
IDictionary *ControladorCurso::ListarCursosNoHabilitados()
{
    IIterator *itc;
    IDictionary *cursosNoHabilitados = new OrderedDictionary();
    Curso *curso;
    for (itc = this->cursos->getIterator(); itc->hasCurrent(); itc->next())
    {
        curso = dynamic_cast<Curso *>(itc->getCurrent());
        if (curso->getHabilitado() == false)
        {
            DataCursoHabMini *dataCurso = new DataCursoHabMini(curso->getNombreCurso());
            OrderedKey *key = new String(curso->getNombreCurso().c_str());
            cursosNoHabilitados->add(key, dataCurso);
            // delete key; efectivamente da problema si se borra la key
        }
    }
    delete itc;
    return cursosNoHabilitados;
}

void ControladorCurso::habilitar_curso(std::string Nombrecurso)
{
    OrderedKey *pepe = new String(Nombrecurso);
    Curso *curso;
    curso =(Curso *)(this->cursos->find(pepe));

    if (curso!=nullptr)
    {
        if(curso->getLecciones()->isEmpty()&&curso->TieneLeccionConEjercicios()){
            std::cout<<"El curso no cumple con todos los requisitos para habilitarse"<<std::endl;
            
        }else{
            curso->setHabilitado(true);

        }
    }
delete pepe;
}

//************************************************************************************//
// adicionales

void ControladorCurso::setCursoActual(Curso *curso)
{
    this->cursoActual = curso;
}

Curso *ControladorCurso::ObtenerCurso(std::string nombrecurso)
{
    OrderedKey *ikp = new String(nombrecurso);
    ICollectible *ic = this->cursos->find(ikp);
    delete ikp;

    if (ic != nullptr)
    {
        return dynamic_cast<Curso *>(ic);
    }
    else
    {
        return nullptr;
    }
}

//************************************************************************************//
// 9 - Eliminar Curso

void ControladorCurso::EliminarCurso(std::string nombreCurso) {
    
Curso * curso = this->ObtenerCurso(nombreCurso);
    if(curso == nullptr){
        std::cout << "No existe curso con Nombre Curso: " << nombreCurso << std::endl;
        return;
    }
    //Eliminamos las lecciones y los ejercicios
    curso->EliminarLecciones(); 
    IDictionary * registros = curso->getRegistroInscripcion();
    IIterator * it = registros->getIterator();
    //Eliminamos los registros de inscripciones
    while (it->hasCurrent())
    {
        Registro * r = dynamic_cast<Registro*>(it->getCurrent());
        if (r != nullptr)
        {
            r->eliminarRegistrodeCurso(r); //REVISAR, PROBABLE QUE ESTE MAL JEJE
        }
        it->next();
    }
    delete it;

    
    //Desvincular los estudiantes del curso
    //HACER!
    // La operacion que hice en Estudiante.cpp, desvincula el curso de la coleccion de registros del estudiante.
    // EN este caso, que tengo que desvincular todos los estudiantes que tengo en la coleccion de estudiantes
    //Estaria bien si yo itero en la coleccion de estudiantes del curso, y por cada estudiante, llamo a la operacion que hice?


    OrderedKey * Ik = new String(nombreCurso);
    
    // Remover el curso de la coleccion de cursos del profesor
    Profesor * profe = Cuser->ObtenerProfesor(curso->getProfesorCurso());
    IDictionary * cursosprofe = profe->getCursosProfesor();
    if (cursosprofe->member(Ik)) //Si el curso que quiero eliminar pertenece a la coleccion de cursos del profesor, lo remuevo
    {
        cursosprofe->remove(Ik);
    }

    
    //Vaciar la coleccion de cursos previos de el curso que quiero eliminar
    //No se si es la idea removerlo de esta manera, o directamente eliminarlo porque es una coleccion unica de cada curso.
    //No me convence, porque estos cursos previos tienen tambien cursos previos, que pasa con eso? Queda en el aire?
    IDictionary * cursosprevios = curso->getCursosPreviosCurso();
    IIterator * itc = cursosprevios->getIterator();
    while (itc->hasCurrent())
    {
        Curso * c = dynamic_cast<Curso*>(itc->getCurrent());
        if (c != nullptr)
        {
            OrderedKey * key = new String(c->getNombreCurso());
            cursosprevios->remove(key);
        }
        itc->next();
    } //Quizas no es necesario hacer todo esto para vaciar esa coleccion y hay una forma mas facil.
    delete itc;

    

    //Averiguar si el curso que quiero borrar, pertenece como previa de alguna otra materia
    // remover el curso de la coleccion de cursos previos
    //Tengo que entrar a la coleccion de cursos previos, y entrar a la coleccion de cursos previos de cada uno
    //Preguntar si el curso que quiero borrar es miembro

    IDictionary * TodosLosCursos = this->cursos; //Obtengo todos los cursos del controlador
    IIterator * Itt = TodosLosCursos->getIterator();

    while (Itt->hasCurrent()) // Voy a recorrer cada curso y sus cursos previos, para ver si el curso que quiero eliminar, es previa de alguno de estos cursos.
    {
        Curso * ct = dynamic_cast<Curso*>(Itt->getCurrent());
        if (ct != nullptr)
        {
            IDictionary * cprevios = ct->getCursosPreviosCurso();
            IIterator * itp = cprevios->getIterator();
            while (itp->hasCurrent()) // Recorro los cursos previos, preguntando si el curso que quiero eliminar, esta.
            {
                Curso * cp = dynamic_cast<Curso*>(itp->getCurrent());
                if (cp != nullptr && (cp->getNombreCurso() == nombreCurso)) // Si ese curso previo es igual al curso que quiero eliminar, lo tengo que remover
                {//No se si esta bien asi o usar el member.
                    cprevios->remove(Ik); //Remuevo el curso que quiero eliminar, con la Key que cree mas arriba.                    
                }
                itp->next();
            }
            delete itp;
        }
        Itt->next();
    }
    delete Itt;
    

    this->cursos->remove(Ik);
}



//************************************************************************************//
// 10 - Consultar Curso
// listar cursos

IDictionary *ControladorCurso::ListarCursos()
{
    IIterator *itc;
    Curso *c;

    IDictionary *auxlistcursos = new OrderedDictionary();

    for (itc = this->cursos->getIterator(); itc->hasCurrent(); itc->next())
    {

        c = (Curso *)itc->getCurrent();
        OrderedKey *ok = new String(c->getNombreCurso().c_str());
        auxlistcursos->add(ok, c);
    }

    return auxlistcursos;
}

IDictionary *ControladorCurso::ListarLeccionesCurso(std::string nombrecurso)
{
    OrderedKey *key = new String(nombrecurso);
    if (this->cursos->member(key))
    {
        Curso *curso = dynamic_cast<Curso *>(this->cursos->find(key));
        if (curso != nullptr)
        {
            delete key;
            return curso->getLecciones();
        }
        else
        {
            std::cout << "Error al obtener el curso" << std::endl;
        }
    }
    else
    {
        std::cout << "No existe el curso con el nombre: " << nombrecurso << std::endl;
    }
    delete key;
    return nullptr;
}

IDictionary *ControladorCurso::ListarEjerciciosLecciones(std::string nombrecurso, std::string temaleccion)
{
    OrderedKey *key = new String(nombrecurso);
    if (this->cursos->member(key))
    {
        Curso *curso = dynamic_cast<Curso *>(this->cursos->find(key));
        delete key; // si da problema lo borro
        if (curso != nullptr)
        {
            IIterator *it = curso->getLecciones()->getIterator();
            while (it->hasCurrent())
            {
                Leccion *leccion = dynamic_cast<Leccion *>(it->getCurrent());
                if (leccion != nullptr && leccion->getTema() == temaleccion)
                {
                    delete it;
                    return leccion->getEjerciciosLeccion();
                }
                it->next();
            }
            delete it;
        }
    }
    delete key;
    return nullptr;
}

IDictionary* ControladorCurso::ListarInscripciones(std::string nombrecurso){
    OrderedKey * key = new String(nombrecurso);
    if(cursos->member(key)){
        Curso * curso = ObtenerCurso(nombrecurso);
        if(curso != nullptr){
            IDictionary * registros = curso->getRegistroInscripcion();
            IIterator * itr = registros->getIterator();
            IDictionary * inscripciones = new OrderedDictionary();
            while(itr->hasCurrent()){
                Registro * registro = dynamic_cast<Registro*>(itr->getCurrent());
                if(registro != nullptr){
                    Estudiante * estudiante = registro->getEstudiante();
                    if(estudiante != nullptr){
                        std::string nombreEstudiante = estudiante->getNickname();
                        OrderedKey * ekey = new String(nombreEstudiante);
                        Date FechaIns = registro->getFechaRegistro();

                        InscripcionInfo * infoins = new InscripcionInfo(nombreEstudiante,FechaIns);
                        inscripciones->add(ekey, infoins);
                    }
                }
                itr->next();
            }
            return inscripciones;
        }
    }else{
        std::cout << "No existe el curso con el nombre: " << nombrecurso << std::endl;
        delete key;  
        return nullptr;
    }
}

//************************************************************************************//
//11 - inscribir curso
IDictionary * ControladorCurso::ListarDataCurso(){
    IDictionary * cursoHab = new OrderedDictionary();

    IIterator * it = this->cursos->getIterator();
    while(it->hasCurrent()){
        Curso * curso = dynamic_cast<Curso*>(it->getCurrent());
        if(curso != nullptr){
            std::string nomcurso = curso->getNombreCurso();
            std::string descurso = curso->getDescripcionCurso();
            TipoDificultad dificultad = curso->getDificultad();
            bool cursohab = curso->getHabilitado();
            std::string idiomaCurso = curso->GetIdiomaCurso();
            std::string profeCurso = curso->getProfesorCurso();

            IDictionary * dleccion = new OrderedDictionary();
            IIterator * itl = curso->getLecciones()->getIterator();
            while(itl->hasCurrent()){
                Leccion * leccion = dynamic_cast<Leccion*>(itl->getCurrent());
                DataLeccion * dataLeccion = nullptr;
                if(leccion != nullptr){
                    std::string temal = leccion->getTema();
                    std::string objetivol = leccion->getObjetivo();
                    IDictionary * dejercicios = new OrderedDictionary();
                    IIterator * ite = leccion->getEjerciciosLeccion()->getIterator();
                    while(ite->hasCurrent()){
                        Ejercicio * ejercicio = dynamic_cast<Ejercicio*>(ite->getCurrent());
                        if(ejercicio != nullptr){
                            std::string efrase = ejercicio->getFrase();
                            std::string edescripcion = ejercicio->getDescripcion();

                            DataEjercicio * dataEjercicio = nullptr;
                            
                            Traduccion * eTraduccion = dynamic_cast<Traduccion*>(ite->getCurrent());
                            CompletarPalabras * eCompletarPalabras = dynamic_cast<CompletarPalabras*>(ite->getCurrent());

                            if(eTraduccion != nullptr){
                                std::string efraseCorrectaT = eTraduccion->getFraseCorrecta();
                                dataEjercicio = new DataEjercicioTraduccion(efrase, edescripcion, efraseCorrectaT);
                            }else if(eCompletarPalabras != nullptr){
                                std::string ePalabras = eCompletarPalabras->getPalabras();
                                dataEjercicio = new DataEjercicioCompletarPalabras(efrase, edescripcion, ePalabras);
                            }

                            if(dataEjercicio != nullptr){
                                OrderedKey * ejerciciokey = new String(edescripcion);
                                dejercicios->add(ejerciciokey,dataEjercicio);
                            }

                        }
                        ite->next();
                    }
                    delete ite;
                    OrderedKey * leccionkey = new String(temal);
                    dataLeccion = new DataLeccion(temal, objetivol, dejercicios);
                    dleccion->add(leccionkey,dataLeccion);
                }
                itl->next();
            }
            delete itl;
            OrderedKey * cursokey = new String(nomcurso);
            DataCursoHab * dcurso = new DataCursoHab(nomcurso, descurso, dificultad, cursohab, idiomaCurso, profeCurso, dleccion);
            cursoHab->add(cursokey, dcurso);
        }
        it->next();
    }
    delete it;
    return cursoHab;
}

//************************************************************************************//
// 12 
IDictionary* ControladorCurso::ListarEjerciciosNoAprobadosDeLeccion(std::string Nombrecurso, std::string Nickname) {
    IDictionary* ejerciciosNoAprobados = new OrderedDictionary();
    IDictionary* lecciones = new OrderedDictionary();
    // Obtener el curso por nombre
    Curso* curso = ObtenerCurso(Nombrecurso);
    if (curso == nullptr) {
        std::cout << "No existe curso con nombre " << Nombrecurso << std::endl;
        return nullptr;
    }
    Estudiante* estudiante = Cuser->ObtenerEstudiante(Nickname);
    if(estudiante==nullptr) {
        std::cout << "No existe estudaiante con nombre " << Nickname << std::endl;
        return nullptr;

    }
    Registro* registro = dynamic_cast<Registro*>(estudiante->getRegistro(Nombrecurso));
    if(registro==nullptr) {
        return nullptr;
    }
    lecciones=curso->getLecciones();
    if(lecciones->isEmpty()) {
        return nullptr;
    }
    Leccion* leccion = curso->ultimaLeccionNoAprobada(estudiante, Nombrecurso);

        if (leccion !=nullptr) {
            // Iterar a través de los ejercicios de la lección
            IIterator* itEjercicios = leccion->getEjerciciosLeccion()->getIterator();
            while (itEjercicios->hasCurrent()) {
                Ejercicio* ejercicio = dynamic_cast<Ejercicio*>(itEjercicios->getCurrent());
                if (ejercicio !=nullptr && !ejercicio->getAprobado()) {
                    IKey* keyEjercicio = new String(ejercicio->getDescripcion());
                    ejerciciosNoAprobados->add(keyEjercicio,ejercicio);
                }
                itEjercicios->next();
            }
            delete itEjercicios;
        }
    return ejerciciosNoAprobados;
}



bool ControladorCurso::Verificarsoluciontraduccion(Traduccion* T, std::string SolucionIngresada) {
    std::string fraseCorrecta = T->getFraseCorrecta();
    
    if (SolucionIngresada == fraseCorrecta) {
        T->setAprobado(true);
        return true;
    } else {
        return false;
    }
}

bool ControladorCurso::VerificarsolucionCompletarPlabra(CompletarPalabras* CP, std::string SolucionIngresadaC) {
    std::string pepe = CP->getPalabras();
    std::stringstream ssSolucion(pepe);
    std::stringstream ssEntrada(SolucionIngresadaC);

    std::string palabraSolucion, palabraEntrada;

    while (std::getline(ssSolucion, palabraSolucion, ',') && std::getline(ssEntrada, palabraEntrada, ',')) {
        if (palabraSolucion != palabraEntrada) { 
            return false;
        }
    }
    //compara las variables y si una tiene mas palabras que la otra retorna false
    if(std::getline(ssSolucion, palabraSolucion, ',') || std::getline(ssEntrada, palabraEntrada, ',')){
        return false;
    }

    CP->setAprobado(true);
    return true;
}

double ControladorCurso::CalcularporcentajeAprobacion(std::string nicknameusuario, std::string nomcurso) {

    Estudiante* e = Cuser->ObtenerEstudiante(nicknameusuario);
    if(e == nullptr) {
        std::cout << "El estudiante no existe." << std::endl;
        return 0.0;
    }

    Curso* curso = this->ObtenerCurso(nomcurso);
    if (curso == nullptr) {
        std::cout << "Curso no encontrado: " << nomcurso << std::endl;
        return 0.0;
    }
    Registro* r = dynamic_cast<Registro*>(e->getRegistro(nomcurso));
    if (r == nullptr) {
        std::cout << "Registro del curso no encontrado: " << std::endl;
        return 0.0;
    }
    //hasta aca bien


    //aca estaba iterando sobre todos los estudiantes inscriptos al curso y generando mal el porcentaje de aprobacion.
    /* int totalEjercicios = curso->getTotalEejercicios();
    if (totalEjercicios == 0) {
        return 0.0;
    }
    double porcentajeAprobacion;
    int totalEjerciciosAprobados = 0;
    IDictionary* registrosInscripcion = curso->getRegistroInscripcion();
    IIterator* it = registrosInscripcion->getIterator();
    while (it->hasCurrent()) {
        Registro* registro = dynamic_cast<Registro*>(it->getCurrent());
        if (registro != nullptr) {
            totalEjerciciosAprobados += registro->getEjerciciosAprobados()->getSize();
        }
        it->next();
    }
    delete it; */

    //Aqui ahora  estaria calculando solo de un estudiante en un curso
    int totalEjercicios = 0;
    IIterator* it = curso->getLecciones()->getIterator();
    while(it->hasCurrent()){
        Leccion * leccion = dynamic_cast<Leccion*>(it->getCurrent());
        if(leccion != nullptr){
            totalEjercicios += leccion->getEjerciciosLeccion()->getSize();
        }
        it->next();
    }
    delete it;

    if(totalEjercicios == 0){
        return 0.0;
    }

    double porcentajeAprobacion;
    int totalEjerciciosAprobados = r->getEjerciciosAprobados()->getSize();
    
    porcentajeAprobacion = (static_cast<double>(totalEjerciciosAprobados) / totalEjercicios) * 100.0;
    r->setPorcentajeAprobacion(porcentajeAprobacion);
    return porcentajeAprobacion;
}


DataEstadisticaCurso* ControladorCurso::consultarEstadisticasCurso(std::string nombreCurso) {
    Curso* curso = this->ObtenerCurso(nombreCurso);
    if (curso == nullptr) {
        std::cout << "Curso no encontrado" << std::endl;
        return nullptr;
    }

    IDictionary* registros = curso->getRegistroInscripcion();
    IIterator* it = registros->getIterator();
    double sumaPorcentajes = 0.0;
    int cantidadEstudiantes = 0;

    while (it->hasCurrent()) {
        Registro* registro = dynamic_cast<Registro*>(it->getCurrent());
        if (registro != nullptr) {
            sumaPorcentajes += registro->getPorcentajeAprobacion();
            cantidadEstudiantes++;
        }
        it->next();
    }
    delete it;

    double promedioAvance = cantidadEstudiantes > 0 ? sumaPorcentajes / cantidadEstudiantes : 0.0;
    std::string descripcion = curso->getDescripcionCurso();
    TipoDificultad dificultad = curso->getDificultad();
    return new DataEstadisticaCurso(nombreCurso, promedioAvance, descripcion, dificultad);
}