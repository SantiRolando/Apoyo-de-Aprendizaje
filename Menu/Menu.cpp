#include <iostream>
#include "Menu.h"
#include "Functions.h"
#include <set>
#include <vector>

Fabrica* fab = Fabrica::getInstance();

InterfazUsuario * ControladorU = fab->Usuario();
InterfazCurso * ControladorC = fab->Curso();

static HandlerIdioma * idiomashandler = HandlerIdioma::getInstance();


//************************************************************************************//

void statusMenu(int opcion){

};


void mostrarMenu(){
    statusMenu(0);
    std::cout << "\n1 - Alta de Usuario" << std::endl;
    std::cout << "2 - Consulta de Usuario" << std::endl;
    std::cout << "3 - Alta de Idioma" << std::endl;
    std::cout << "4 - Consultar Idiomas" << std::endl;
    std::cout << "5 - Alta de Curso" << std::endl;
    std::cout << "6 - Agregar Leccion" << std::endl;
    std::cout << "7 - Agregar Ejercicio" << std::endl;
    std::cout << "8 - Habilitar Curso" << std::endl;
    std::cout << "9 - Eliminar Curso" << std::endl;
    std::cout << "10 - Consultar Curso" << std::endl;
    std::cout << "11 - Inscribirse a Curso" << std::endl;
    std::cout << "12 - Realizar Ejercicio" << std::endl;
    std::cout << "13 - Consultar Estadisticas" << std::endl;
    std::cout << "14 - Pre-cargar datos en el sistema" << std::endl;
    std::cout << "15 - Salir del sistema" << std::endl;
}

int obteneropcionMenu() {
    int opcion = 0;
    mostrarMenu();
    std::cout << "> ";
    while (!(std::cin >> opcion) || opcion < 1 || opcion > 15){
        system("clear");
        mostrarMenu();
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Ingrese una opción válida\n" << std::endl;
        std::cout << ">... ";
    }
    clearBuffer();
    return opcion;
}

void clearBuffer(){
    char aux;
    while ((aux = getchar()) != '\n' && aux != EOF){
        //Nada, limpia buffer
    }
}

//************************************************************************************//
//1
void AltaUsuario(){
    
    bool valido = false;
    std::string nicknameuser;
    std::string descripcionuser;
    std::string contraseniauser;
    std::string nombreuser;
    std::string pais;
    Date fechaNac;
    std::string instituto;
    std::string idioma;
    system("clear");
    printTitleInBox("Alta Usuario");

    nicknameuser = pedirString("el nickname del usuario");
    nombreuser = pedirString("el nombre del usuario");
    descripcionuser = pedirString("la descripcion del usuario");
    contraseniauser = pedirContrasenia("la contrasenia del usuario");

    int opcion;
    std::cout << "\n";
    std::cout << "1 - Ingresar un Estudiante" << std::endl;
    std::cout << "2 - Ingresar un Profesor" << std::endl;
    opcion = obteneropcion();

    switch(opcion){
        case 1:
            //Alta Estudiante
            system("clear");
            //std::cin.ignore();
            std::cin.clear();
            printTitleInBox("Alta Estudiante");
            pais = pedirString("el pais del estudiante");
            fechaNac = pedirFecha("la fecha de nacimiento del estudiante");
            std::cout << "\nEstudiante: \n" << std::endl;
            std::cout << "Nickname: " << nicknameuser << std::endl;
            std::cout << "Nombre: " << nombreuser << std::endl;
            std::cout << "Descripcion: " << descripcionuser << std::endl;
            std::cout << "Contrasenia: " << contraseniauser << std::endl;
            std::cout << "Pais: " << pais << std::endl;
            std::cout << "Fecha Nacimiento: " << dateToString(fechaNac);
            std::cout << std::endl;
            loading("Dando de alta al estudiante");
            std::cout << std::endl;
            ControladorU->ConfirmarAltaEstudiante(nicknameuser, nombreuser , descripcionuser, contraseniauser, pais, fechaNac);
            std::cout << std::endl;
            pausa("Presione enter para continuar...");
            break;
        case 2:
            //Alta profesor
            system("clear");
            std::cin.clear();
            printTitleInBox("Alta Profesor");

            if(idiomashandler->getIdiomasH()->isEmpty()){
                std::cout << "Por el momento no hay idiomas en el sistema, primero ingrese un idioma" << std::endl;
                pausa("Presione enter para continuar...");
                return;
            }
            instituto = pedirString("el instituto del profesor");
            std::cout << std::endl;
            ControladorU->ConfirmarAltaProfesor(nicknameuser, nombreuser, descripcionuser, contraseniauser, instituto);
            std::cout << std::endl;

            Profesor * profesor = ControladorU->ObtenerProfesor(nicknameuser);
            ControladorU->SetProfesorActual(profesor);
            //pausa("Presione enter para continuar...");

            //listar
            IDictionary * listaidiomas = new OrderedDictionary();
            listaidiomas = idiomashandler->ListarIdiomas();
            IIterator * iti;
            loading("Cargando lista de idiomas");
            std::cout << std::endl;
            std::cout << std::endl;
            for(iti = listaidiomas->getIterator(); iti->hasCurrent(); iti->next()){
                if(Idioma * i = dynamic_cast<Idioma*>(iti->getCurrent())){
                    std::cout << "Nombre del idioma: " << i->getNombreIdioma() << std::endl;
                }
            }
            delete iti;
            //termina listar

            std::cout << std::endl;
            while (true) {
                idioma = pedirString("el idioma en el que se especializa (obligatorio)");
                if (!idioma.empty()) {
                    OrderedKey* key = new String(idioma);
                    if (idiomashandler->getIdiomasH()->member(key)) {
                        loading("Agregando idioma al profesor");
                        std::cout << std::endl;
                        ControladorU->AgregarIdioma(idioma);
                        delete key;
                        break;
                    } else {
                        std::cout << "El idioma ingresado no está en la lista de idiomas del sistema. Intente nuevamente.\n";
                    }
                    delete key;
                } else {
                    std::cout << "Debe ingresar al menos un idioma.\n";
                }
            }

            // Ingreso opcional de más idiomas
            while (true) {
                idioma = pedirString("otro idioma en el que se especializa (o ingrese 'fin' para terminar)");
                if (idioma == "fin") {
                    break;
                } else if (!idioma.empty()) {
                    OrderedKey* key = new String(idioma);
                    if (!profesor->getIdiomasProfesor()->member(key)) {
                        loading("Agregando idioma al profesor");
                        ControladorU->AgregarIdioma(idioma);
                    } else {
                        std::cout << "El idioma ya está agregado.\n";
                    }
                    delete key; // Liberar memoria de la clave creada
                }
            }

            std::cout << std::endl;
            pausa("Presione enter para continuar...");
            delete listaidiomas;  
            break; 
   }
} 

void ConsultaUsuarios(){
    system("clear");
    std::string nicknameuser;
    Estudiante * e;
    Profesor * p;

    printTitleInBox("Lista de usuarios");
    IDictionary * listaUsuarios = new OrderedDictionary;

    loading("Listando Usuarios");
    std::cout << "\n" << std::endl;
    listaUsuarios = ControladorU->ObtenerUsuarios(); //muestra el nickname estudiantes
    if(listaUsuarios->isEmpty()){
        std::cout << "N/A" << std::endl;
        pausa("Presione enter para continuar...");
        return;
    }else{
        IIterator* ite;
        for(ite = listaUsuarios->getIterator(); ite->hasCurrent(); ite->next()){
            if(e = dynamic_cast<Estudiante*>(ite->getCurrent())){
                std::cout << "Nickname del estudiante: " << e->getNickname() << std::endl;
            }else{
                p = dynamic_cast<Profesor*>(ite->getCurrent());
                std::cout << "Nickname del profesor: " << p->getNickname() <<std::endl;
            }
        }
        delete ite;
        std::cout << std::endl;
        nicknameuser = pedirString("el nickname del usuario para mostrar su informacion");
        
        DataEstudiante * dte;
        DataProfesor * dtp;

        //ingresa nickname y muestra la otra informacion basica del estudiante
        if(dte = dynamic_cast<DataEstudiante*>(ControladorU->InformacionUsuario(nicknameuser))){
            std::cout << "\nInformacion del Usuario\n" << std::endl;
            std::cout << "Nickname del estudiante: " << dte->getNickname() << std::endl;
            std::cout << "Descripcion del estudiante: " << dte->getDescripcion() << std::endl;
            std::cout << "Pais del estudiante: " << dte->getPais() << std::endl;
            std::cout << "Fecha nacimiento del estudiante: " << dte->getFechaNac().day << "/" << dte->getFechaNac().month << "/" << dte->getFechaNac().year << std::endl;
            


           IDictionary * cursitos = dte->getCursosInscriptoDT();
           if(cursitos->isEmpty()){
            std::cout << "No esta inscripto a ningun curso" << std::endl;
           }else{
            std::cout << "Cursos Inscripto: " << std::endl;
            IIterator * itce = cursitos->getIterator();
            std::cout << std::endl;
            while(itce->hasCurrent()){
                Curso * curso = dynamic_cast<Curso*>(itce->getCurrent());
                if(curso){
                    std::cout << "- " << curso->getNombreCurso() <<std::endl;
                }
                itce->next();
            }
            delete itce;
           }
        }else if(dtp = dynamic_cast<DataProfesor*>(ControladorU->InformacionUsuario(nicknameuser))){
            std::cout << "\nInformacion del Usuario\n" << std::endl;
            std::cout << "Nickname del profesor: " << dtp->getNickname() << std::endl;
            std::cout << "Descripcion del profesor: " << dtp->getDescripcion() << std::endl;
            std::cout << "Instituto del profesor: " << dtp->getInstituto();
            
            IIterator * it = listaUsuarios->getIterator();
            while (it->hasCurrent()){
                ICollectible* icu = it->getCurrent();
                p = dynamic_cast<Profesor*>(icu);
                if (p != nullptr && p->getNickname() == nicknameuser) {
                    IDictionary* idiomas = new OrderedDictionary();
                    idiomas = p->getIdiomasProfesor();
                    if (idiomas->isEmpty()) {
                        std::cout << "\nNo tiene idiomas asignados" << std::endl;
                    } else {
                        std::cout << "\nIdiomas que enseña: \n" << std::endl;
                        IIterator* itIdiomas;
                        for(itIdiomas = idiomas->getIterator(); itIdiomas->hasCurrent(); itIdiomas->next()){
                            Idioma* idioma = dynamic_cast<Idioma*>(itIdiomas->getCurrent());
                            std::cout << "- " << idioma->getNombreIdioma() << std::endl;
                        }
                        delete itIdiomas;
                    }
                    break;
                }
                it->next();
            }
            delete it;    
        }else{
            std::cout << "\nNo existe ningun usuario con nickname: " << nicknameuser << std::endl;
        }
        //delete ite
    }
    //std::cout << std::endl;
    pausa("Presione enter para continuar...");
    delete listaUsuarios;
}

//************************************************************************************//
//3
void AltaIdioma(){

    std::string idioma;

    system("clear");
    printTitleInBox("Alta Idioma");
    idioma = pedirString("un idioma para agregarlo al sistema");
    loading("Dando de alta el idioma");
    std::cout << "\n" << std::endl;
    idiomashandler->AltaIdioma(idioma);
    std::cout << "\n" << std::endl;
    pausa("Presione enter para continuar...");

}

//************************************************************************************//
//4
void ConsultarIdiomas(){

    system("clear");
    printTitleInBox("Consultar Idiomas");
    
    IDictionary * listai = new OrderedDictionary();
    loading("Listando Usuarios");
    std::cout << "\n" << std::endl;

    listai = idiomashandler->ListarIdiomas();
    if(listai->isEmpty()){
        std::cout << "N/A" << std::endl;
    }else{
        IIterator * iti;
        for(iti = listai->getIterator(); iti->hasCurrent(); iti->next()){
            Idioma * i = dynamic_cast<Idioma*>(iti->getCurrent());
            std::cout << "Nombre Idioma: " <<  i->getNombreIdioma() << std::endl;
        }
        delete iti;
    }
    pausa("Presione enter para continuar...");
}

//************************************************************************************//
//5
void AltaCurso(){

    //Curso
    std::string nicknamep;
    std::string nombrecurso;
    std::string descripcioncurso;
    TipoDificultad dificultadcurso;
    IDictionary * listaIdiomasProfesor;
    std::string idiomacurso;
    std::string cursoprevio;

    //Leccion
    std::string tema;
    std::string objetivo;

    //Ejercicio
    std::string frase;
    std::string descripcionejercicio;
    //Ejercicio Traduccion
    std::string frasecorrectatraduccion;
    //Ejercicio Completar Palabras
    std::string palabras;

    system("clear");
    printTitleInBox("Alta Curso");

    IDictionary * listaprofes;
    listaprofes = ControladorU->ListarProfesores();

    if(listaprofes->isEmpty()){
        std::cout << "No hay profesores ingresados todavia." << std::endl;
        return;
    }else{
        IIterator * itp;
        for(itp = listaprofes->getIterator(); itp->hasCurrent(); itp->next()){
            Profesor * p = dynamic_cast<Profesor*>(itp->getCurrent());
            std::cout << "Nickname Profesor: " << p->getNickname() << std::endl;
        }
        delete itp;
    }
    std::cout << "\n";
    nicknamep = pedirString("el profesor que dictara el curso");
    bool valido = ControladorU->ExisteProfesor(nicknamep);
    if(valido != true){
        std::cout << "No existe profesor con " << nicknamep << "en el sistema" << std::endl;
        return;
    }
    
    nombrecurso = pedirString("el nombre del curso");
    descripcioncurso = pedirString("la descripcion del curso");
    int dif;
    std::cout << "\n1 - Principiante" << std::endl;
    std::cout << "2 - Medio" << std::endl;
    std::cout << "3 - Avanzado\n" << std::endl;
    dif = pedirInt("la dificultad que tendra el curso (1/2/3)");

    switch(dif){
        case 1:
            dificultadcurso = Principiante;
            break;
        case 2:
            dificultadcurso = Medio;
            break;
        case 3:
            dificultadcurso = Avanzado;
            break;
        default:
            std::cout << "Ingrese una opcion valida" << std::endl;
            break;
    }

    //loading("Dando de alta el curso");
    listaIdiomasProfesor = ControladorC->IngresarCurso(nicknamep, nombrecurso, descripcioncurso, dificultadcurso);
    Profesor * profesor = ControladorU->ObtenerProfesor(nicknamep);
    Curso * curso = ControladorC->ObtenerCurso(nombrecurso);
    ControladorC->setCursoActual(curso);
    profesor->AgregarCursoProfesor(curso);
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << std::endl;
    IIterator * it = listaIdiomasProfesor->getIterator();
    //int i = 1;
    while(it->hasCurrent()){
        Idioma * idioma = dynamic_cast<Idioma*>(it->getCurrent());
        std::cout << idioma->getNombreIdioma() << std::endl;
        //i += 1;
        it->next();
    }
    delete it;
    //std::cin.ignore();
    bool profesorTieneIdioma;
    std::cout << std::endl;//fijar si sirve
    idiomacurso = pedirString("el idioma en el que se dicatara el curso");
    profesorTieneIdioma = ControladorU->IdiomaPerteneceAProfesor(nicknamep,idiomacurso);
    ControladorC->AgregarIdiomaCurso(idiomacurso);
    //std::cout << "Profesor tiene idioma?: " << profesorTieneIdioma << std::endl;

    if(!profesorTieneIdioma){
        std::cout << nicknamep << " no se especializa en el idioma " << idiomacurso << std::endl;
    }else{  
        if (!curso) {
            std::cout << "Error al obtener el curso" << std::endl;
            return;
        }
        ControladorC->setCursoActual(curso);
        std::cout << "Curso " << nombrecurso << " asignado correctamente." << std::endl;
        bool continuar = true;
        IDictionary * cursoshabilitados = ControladorC->ListarCursosHabilitados();

        
        ////////////////////////agregar cursos previos a curso////////////////////////
        do{
            std::cout << "\nEste curso requiere de un curso previo? s/n" << std::endl;
            char confirmacion;
            std::cout <<">... ";
            std::cin >> confirmacion;
            confirmacion = std::tolower(confirmacion);

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (confirmacion == 's') {
                std::cout << std::endl;
                std::cout << "Lista de cursos habilitados:" << std::endl;
                std::cout << std::endl;
                if(cursoshabilitados->isEmpty()){
                    std::cout << "No hay cursos habilitados" << std::endl;
                    std::cout << std::endl;
                    continuar = false;
                }else{
                    IIterator * it;
                    DataCursoHabMini * datacurso;
                    for(it = cursoshabilitados->getIterator(); it->hasCurrent(); it->next()){
                        datacurso = dynamic_cast<DataCursoHabMini*>(it->getCurrent());
                        if(datacurso != nullptr){
                            std::cout << "Nombre Curso: " << datacurso->getNombreCurso() << std::endl;
                        }
                    }
                    delete it;
                    //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    cursoprevio = pedirString("el curso que sera requerido como previo ");
                    Curso * cur = ControladorC->ObtenerCurso(cursoprevio);
                    if(!cur){
                        return;
                    }
                    curso = ControladorC->ObtenerCurso(nombrecurso);
                    ControladorC->setCursoActual(curso);
                    ControladorC->AgregarCursoPrevio(cursoprevio);
                    std::cout << std::endl;
                }

            }else{
                continuar = false;
            }
        }while(continuar);
        ////////////////////////////////////////////////////////////////////////////

        ////////////////////////agregar lecciones a curso////////////////////////
        curso = ControladorC->ObtenerCurso(nombrecurso);
        ControladorC->setCursoActual(curso);
        bool continuar2 = true;
        do{
            std::cout << "Desea agregar lecciones a este curso s/n" << std::endl;
            char confirmacion;
            std::cout <<">... ";
            std::cin >> confirmacion;
            confirmacion = std::tolower(confirmacion);
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if(confirmacion == 's'){

                tema = pedirString("el tema que tratara la leccion");
                objetivo = pedirString("el objetivo que tendra la leccion");

                ControladorC->AgregarLeccion(tema, objetivo, nombrecurso);
                ////////////////////////////////Agregar Ejercicios a Leccion////////////////////////////////
                
                bool continuar3 = true;
                do{
                    std::cout << "Desea agregar ejercicios a esta leccion s/n" << std::endl;
                    char confirmacion;
                    std::cout <<">... ";
                    std::cin >> confirmacion;
                    confirmacion = std::tolower(confirmacion);
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    if(confirmacion == 's'){
                        std::cout << std::endl;
                        descripcionejercicio = pedirString("la descripcion del ejercicio");
                        std::cout << std::endl;
                        std::cout << "Que tipo de ejercicio desea agregar" << std::endl;
                        std::cout << "\n1 - Ejercicio de Completar Palabras" << std::endl;
                        std::cout << "2 - Ejercicio de Traduccion" << std::endl;
                        dif = pedirInt("el ejercicio que desea agregar(1/2)");
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        switch(dif){
                            case 1:
                                frase = pedirString("las frase a completar con formato -> ejemplo: (Mi --- es juan y tengo 21 ---)");
                                palabras = pedirString("el conjunto ordenado de palabras separadas por una coma que conforman la solucion -> ejemplo: (Caso anterior seria nombre,anios )");
                                ControladorC->AgregarEjercicioCompletarPalabras(nombrecurso, tema, frase, descripcionejercicio, palabras);
                                //ControladorC->HabilitarCurso(nombrecurso);
                                break;
                            case 2:

                                frase = pedirString("la frase a traducir -> ejemplo: (Soy juan)");
                                frasecorrectatraduccion = pedirString("la frase traducida -> ejemplo: (I am juan)");
                                ControladorC->AgregarEjercicioTraduccion(nombrecurso, tema, frase, descripcionejercicio, frasecorrectatraduccion);
                                //ControladorC->HabilitarCurso(nombrecurso);
                                break;
                            default:
                                std::cout << "Opcion ingresada invalida" << std::endl;
                                break;
                        }
                    }else{
                        continuar3 = false;
                    }
                }while(continuar3);
                ////////////////////////////////////////////////////////////////////////////////////////////
            }else{
                continuar2 = false;
            }
        }while(continuar2);
        /////////////////////////////////////////////////////////////////////////
    }
    pausa("Presione enter para continuar...");
}

//************************************************************************************//
//6
void AgregarLeccion(){
    
    std::string tema;
    std::string objetivo;
    std::string nombrecurso;
    std::string descripcionejercicio;
    std::string frase;
    std::string frasecorrectatraduccion;
    std::string palabras;


    system("clear");
    printTitleInBox("Agregar Leccion a Curso");
    std::cout << "Lista de cursos no habilitados: " << std::endl;
    std::cout << std::endl;
     IDictionary* key;
     key=ControladorC->ListarCursosNoHabilitados();
     if(key->isEmpty()){
        std::cout<<"No hay cursos no habilitados"<<std::endl;
        pausa("Presione enter para continuar");
        return;
     }else{
        IIterator* it;
        for(it=key->getIterator();it->hasCurrent();it->next()){
            Curso* curso=(Curso*)(it->getCurrent());
            std::cout<<"Los nombre de los cursos no habilitados son:"<<std::endl;
            std::cout<<curso->getNombreCurso()<<std::endl;
        }
        delete it;
     }
   

    nombrecurso=pedirString("nombre del curso");
    
    Curso* curso=ControladorC->ObtenerCurso(nombrecurso);//necesito obtener el curso del cual me pasan el nombre
    if(curso!=nullptr){
    if(curso->getHabilitado()==true){
        std::cout<<"El curso ya esta habilitado"<<std::endl;
        return;
    }
    }else{ 
        std::cout<<"El curso no existe"<<std::endl;
        pausa("Presione enter para continuar");
        return;
    }
     
    tema=pedirString("el tema de la leccion");
    objetivo=pedirString("el objetivo");
    loading("Agregando leccion");
    std::cout << std::endl;
    ControladorC->AgregarLeccion(tema,objetivo,nombrecurso);

  
       if (ControladorC->ExisteLeccion(nombrecurso,tema)){ 
        
        do{
        int elijoeje;
        char opci;
        std::cout<<"¿Quiere ingresar Ejercicios? S/N"<<std::endl;
        std::cin>>opci;
        if(opci=='S'||opci=='s'){
            std::cout<<"¿Que tipo de Ejercicio quiere agregar? 1/2"<<std::endl;
            std::cout<<"\n1-Ejercicio de completar palabras"<<std::endl;
            std::cout<<"\n2-Ejercicio de traduccion"<<std::endl;
            std::cin>>elijoeje;
            descripcionejercicio=pedirString("la descripcion del Ejercicio");
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if(elijoeje==1||elijoeje==2){
                switch (elijoeje)
                {
                case 1:{
                  
                frase = pedirString("la frase a completar con formato -> ejemplo: (Mi --- es Juan y tengo 21 ---)");
                palabras = pedirString("el conjunto ordenado de palabras separadas por una coma que conforman la solucion -> ejemplo: (nombre,anios)");
                ControladorC->AgregarEjercicioCompletarPalabras(nombrecurso,tema,frase,descripcionejercicio,palabras);
                 
                    
                    break;
                }case 2:{
                    frase=pedirString("la frase a traducir -> ejemplo: (Soy Juan)");
                    frasecorrectatraduccion=pedirString("la frase traducida -> ejemplo: (I am Juan)");
                    ControladorC->AgregarEjercicioTraduccion(nombrecurso,tema,frase,descripcionejercicio,frasecorrectatraduccion);
                break;
                }default:
                    break;
                }
        }else{
           std::cout<<"\nLa opcion elegida no es no es correcta"<<std::endl; 
        }
        
        }else{
            if(opci=='n'||opci=='N'){
                break;
            }else{
                std::cout<<"\nLa opcion elegida no es no es correcta"<<std::endl;
            }
        }
        }while(true);


        }else{
std::cout<<"No existe este curso"<<std::endl;
pausa( "Presione enter para continuar...");
delete key;
}
}

void AgregarEjercicio() {
    
    std::string nombrecurso;
    std::string tema;
    std::string descripcionejercicio;
    std::string frase;
    std::string frasecorrectatraduccion;
    std::string palabras;

    bool continuar = true;

    while (continuar) {
        system("clear");
        printTitleInBox("Agregar Ejercicio a Leccion");

        std::cout << "Lista de cursos no habilitados: " << std::endl;
        std::cout << std::endl;

        // Obtener lista de cursos no habilitados
        IDictionary* auxlistcurso = ControladorC->ListarCursosNoHabilitados();
        if (auxlistcurso->isEmpty()) {
            std::cout << "N/A" << std::endl;
        } else {
            IIterator* it;
            DataCursoHabMini* curso;
            for (it = auxlistcurso->getIterator(); it->hasCurrent(); it->next()) {
                curso = dynamic_cast<DataCursoHabMini*>(it->getCurrent());
                if (curso != nullptr) {
                    std::cout << "Nombre Curso: " << curso->getNombreCurso() << std::endl;
                }
            }
            delete it;
        }
        std::cout << std::endl;
        nombrecurso = pedirString("el nombre del curso al que le quiere agregar un ejercicio");

        Curso* curso = ControladorC->ObtenerCurso(nombrecurso);

        if (curso == nullptr) {
            std::cout << "El curso " << nombrecurso << " no existe" << std::endl;
            pausa("Presione enter para continuar");
            //delete auxlistcurso;
            return;
        } else if (curso->getHabilitado()) {
            std::cout << "El curso " << nombrecurso << " no esta disponible, seleccione uno de los cursos no habilitados" << std::endl;
            pausa("Presione enter para continuar");
            //delete auxlistcurso;
            return;
        }

        do {
            std::cout << std::endl;
            std::cout << "Lecciones del curso: " << nombrecurso << std::endl;
            IDictionary* lecciones = ControladorC->ListarLeccionesCurso(nombrecurso);

            if (lecciones != nullptr && !lecciones->isEmpty()) {
                IIterator* itl = lecciones->getIterator();
                int n = 1;
                while (itl->hasCurrent()) {
                    Leccion* leccion = dynamic_cast<Leccion*>(itl->getCurrent());
                    if (leccion != nullptr) {
                        std::cout << std::endl;
                        std::cout << "Tema: " << leccion->getTema() << std::endl;
                    }
                    itl->next();
                }
                delete itl;
            }
            std::cout << std::endl;
            tema = pedirString("el tema de la leccion donde al cual quiere agregar un ejercicio");

            if (!ControladorC->ExisteLeccion(nombrecurso, tema)) {
                std::cout << "La leccion " << tema << " no existe en el curso " << nombrecurso << std::endl;
                pausa("Presione enter para continuar");
                //delete auxlistcurso;
                //delete lecciones;
                return;
            } else {
                do {
                    std::cout << std::endl;
                    std::cout << "Ingrese el tipo de ejercicio que desea agregar:" << std::endl;
                    std::cout << "\n1 - Ejercicio de Completar Palabras" << std::endl;
                    std::cout << "2 - Ejercicio de Traducción\n" << std::endl;
                    int opcionEjercicio = pedirInt("la opcion del ejercicio que desea agregar (1/2)");
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    descripcionejercicio = pedirString("la descripcion del ejercicio");

                    switch (opcionEjercicio) {
                        case 1: {
                            frase = pedirString("la frase a completar con formato -> ejemplo: (Mi --- es Juan y tengo 21 ---)");

                            palabras = pedirString("el conjunto ordenado de palabras separadas por una coma que conforman la solucion -> ejemplo: (nombre,anios)");
                            std::cout << std::endl;
                            ControladorC->AgregarEjercicioCompletarPalabras(nombrecurso, tema, frase, descripcionejercicio, palabras);
                            break;
                        }
                        case 2: {
                            frase = pedirString("la frase a traducir -> ejemplo: (Soy Juan)");

                            frasecorrectatraduccion = pedirString("la frase traducida -> ejemplo: (I am Juan)");
                            std::cout << std::endl;
                            ControladorC->AgregarEjercicioTraduccion(nombrecurso, tema, frase, descripcionejercicio, frasecorrectatraduccion);
                            break;
                        }
                        default:
                            std::cout << "Opción ingresada inválida." << std::endl;
                            break;
                    }

                    std::cout << "Ejercicio agregado exitosamente para la lección \"" << tema << "\" del curso \"" << nombrecurso << "\"." << std::endl;

                    std::cout << std::endl;
                    char respuesta;
                    std::cout << "¿Desea agregar otro ejercicio a esta lección? (s/n): ";
                    std::cin >> respuesta;

                    if (respuesta == 'n' || respuesta == 'N') {
                        break; 
                    }
                } while (true);

                std::cout << std::endl;
                std::cout << "¿Desea agregar ejercicio a otra lección del mismo curso? (s/n): ";
                char respuesta_otra_leccion;
                std::cin >> respuesta_otra_leccion;

                if (respuesta_otra_leccion == 'n' || respuesta_otra_leccion == 'N') {
                    continuar = false;
                }
            }
        } while (continuar);
    }
}
  


//************************************************************************************//
//8
void HabilitarCurso(){
    std::string nombrecurso;
    IDictionary* listanohab;

    system("clear");
    printTitleInBox("Habilitar Curso");
    listanohab=ControladorC->ListarCursosNoHabilitados();
    if(listanohab->isEmpty()){
        std::cout<<"No tiene cursos no habilitado"<<std::endl;
    }else{
        IIterator* it;
        
        for(it=listanohab->getIterator();it->hasCurrent(); it->next()){
            Curso* curso=(Curso*)(it->getCurrent());
            std::cout<<"Nombre del curso: "<<curso->getNombreCurso()<<std::endl;
        }
        delete it;
    }
  
    nombrecurso = pedirString("nombre del Curso");
       Curso* curso =  ControladorC->ObtenerCurso(nombrecurso);
    if(curso!=nullptr){
        if(!curso->getHabilitado()){
    ControladorC->habilitar_curso(nombrecurso);
        }else{
          std::cout<<"El curso ya esta habilitado"<<std::endl;  
            pausa("presione enter para continuar");
            return;
        }
    }else{
        std::cout<<"El curso no existe"<<std::endl;
        pausa("presione enter para continuar");
        return;
    }
}

//************************************************************************************//
//9
void EliminarCurso(){

    std::string nombreCurso;
    system("clear");
    printTitleInBox("Eliminar Curso");

    //Listamos el nombre de los cursos
    IDictionary * listai = new OrderedDictionary();
    loading("Listando cursos");
    std::cout << "\n" << std::endl;

    listai = ControladorC->ListarCursos();
    if(listai->isEmpty()){
        std::cout << "N/A" << std::endl;
        
    }else{
        IIterator * iti;
        for(iti = listai->getIterator(); iti->hasCurrent(); iti->next()){
            Curso * i = dynamic_cast<Curso*>(iti->getCurrent());
            std::cout << "Nombre curso: " <<  i->getNombreCurso() << std::endl;
        }
    }
    
    std::cout << std::endl;
    nombreCurso = pedirString("El nombre del curso que desea eliminar:");

    ControladorC->EliminarCurso(nombreCurso);
    

}

//************************************************************************************//
//10
void ConsultarCurso() {
    system("clear");
    printTitleInBox("Consultar Cursos");

    IDictionary* listai = ControladorC->ListarCursos();
    if (listai->isEmpty()) {
        std::cout << "N/A" << std::endl;
        pausa("Presione enter para continuar...");
        return;
    } else {
        IIterator* iti = listai->getIterator();
        std::cout << "Lista de cursos disponibles:" << std::endl;
        std::cout << std::endl;
        while (iti->hasCurrent()) {
            Curso* i = dynamic_cast<Curso*>(iti->getCurrent());
            std::cout << "Nombre curso: " << i->getNombreCurso() << std::endl;
            iti->next();
        }
        delete iti;
    }
    std::cout << std::endl;
    std::string seleccionarCurso = pedirString(" el nombre del curso que desea consultar");

    Curso* cursoSeleccionado = nullptr;
    IIterator* iti = listai->getIterator();
    while (iti->hasCurrent()) {
        Curso* i = dynamic_cast<Curso*>(iti->getCurrent());
        if (i != nullptr && i->getNombreCurso() == seleccionarCurso) {
            cursoSeleccionado = i;
            break;
        }
        iti->next();
    }
    delete iti;

    if (cursoSeleccionado == nullptr) {
        std::cout << "El curso ingresado no existe" << std::endl;
        pausa("Presione enter para continuar...");
        return;
    }

    std::cout << "\nInformación del curso seleccionado:" << std::endl;
    std::cout << std::endl;
    std::cout << "Nombre curso: " << cursoSeleccionado->getNombreCurso() << std::endl;
    std::cout << "Descripción: " << cursoSeleccionado->getDescripcionCurso() << std::endl;
    std::cout << "Dificultad: " << obtenerTipoDificultad(cursoSeleccionado->getDificultad()) << std::endl;
    std::cout << "Profesor del Curso: " << cursoSeleccionado->getProfesorCurso() << std::endl;
    std::cout << "Habilitado: " << ObtenerBool(cursoSeleccionado->getHabilitado()) << std::endl;
    std::cout << "Idioma del Curso: " << cursoSeleccionado->GetIdiomaCurso() << std::endl;

    // Mostrar lecciones para el curso seleccionado
    IDictionary* leccionescurso = ControladorC->ListarLeccionesCurso(cursoSeleccionado->getNombreCurso());
    if (leccionescurso != nullptr && !leccionescurso->isEmpty()) {
        std::vector<Leccion*> leccionesVec;
        IIterator* itl = leccionescurso->getIterator();
        while (itl->hasCurrent()) {
            Leccion* leccion = dynamic_cast<Leccion*>(itl->getCurrent());
            if (leccion != nullptr) {
                leccionesVec.push_back(leccion);
            }
            itl->next();
        }
        delete itl;

        // Ordenar lecciones por el atributo de orden
        std::sort(leccionesVec.begin(), leccionesVec.end(), [](Leccion* a, Leccion* b) {
            return a->getOrden() < b->getOrden();
        });

        //int n = 1;
        for (Leccion* leccion : leccionesVec) {
            std::cout << std::endl;
            std::cout << "Lección - " << leccion->getOrden()<< std::endl;
            std::cout << "Tema: " << leccion->getTema() << std::endl;
            std::cout << "Objetivo: " << leccion->getObjetivo() << std::endl;
            std::cout << std::endl;
            IDictionary* ejerciciosleccion = ControladorC->ListarEjerciciosLecciones(cursoSeleccionado->getNombreCurso(), leccion->getTema());
            if (ejerciciosleccion != nullptr && !ejerciciosleccion->isEmpty()) {
                IIterator* ite = ejerciciosleccion->getIterator();
                int m = 1;
                while (ite->hasCurrent()) {
                    Ejercicio* ejercicio = dynamic_cast<Ejercicio*>(ite->getCurrent());
                    if (ejercicio != nullptr) {
                        CompletarPalabras* cp = dynamic_cast<CompletarPalabras*>(ejercicio);
                        Traduccion* t = dynamic_cast<Traduccion*>(ejercicio);

                        std::cout << "Ejercicio - " << m << std::endl;
                        if (cp != nullptr) {
                            std::cout << "Tipo: Completar Palabras" << std::endl;
                            std::cout << "Descripción: " << cp->getDescripcion() << std::endl;
                            std::cout << "Frase: " << cp->getFrase() << std::endl;
                            std::cout << "Palabras: " << cp->getPalabras() << std::endl;
                            std::cout << std::endl;
                        } else if (t != nullptr) {
                            std::cout << "Tipo: Traducción" << std::endl;
                            std::cout << "Descripción: " << t->getDescripcion() << std::endl;
                            std::cout << "Frase: " << t->getFrase() << std::endl;
                            std::cout << "Frase Traducida: " << t->getFraseCorrecta() << std::endl;
                            std::cout << std::endl;
                        }
                    }
                    ite->next();
                    m += 1;
                }
                delete ite;
            } else {
                std::cout << "Ejercicios: N/A" << std::endl;
            }
            //n += 1;
        }
    } else {
        std::cout << "Lecciones: N/A" << std::endl;
    }

    // Mostrar inscripciones para el curso seleccionado
    IDictionary* inscripciones = ControladorC->ListarInscripciones(cursoSeleccionado->getNombreCurso());
    if (inscripciones != nullptr && !inscripciones->isEmpty()) {
        IIterator* itins = inscripciones->getIterator();
        int o = 1;
        while (itins->hasCurrent()) {
            InscripcionInfo* insinfo = dynamic_cast<InscripcionInfo*>(itins->getCurrent());
            if (insinfo != nullptr) {
                std::cout << "Inscripción - " << o << std::endl;
                std::cout << "Estudiante: " << insinfo->getEstudianteNombre() << std::endl;
                std::cout << "Fecha de inscripción: " << insinfo->getFechaIns().day << "/" << insinfo->getFechaIns().month << "/" << insinfo->getFechaIns().year << std::endl;
            }
            itins->next();
            o += 1;
        }
        delete itins;
    } else {
        std::cout << "Inscripciones: N/A" << std::endl;
    }

    std::cout << "\n ----------------------------------------" << std::endl;
    pausa("Presione enter para continuar...");
}

//************************************************************************************//
//11
void InscribirseACurso() {

    std::string nickname;
    system("clear");
    printTitleInBox("Inscribir a Curso");
    
    IDictionary * listaUsuarios = new OrderedDictionary();
    Estudiante * e;

    std::cout<<"\n"<< std::endl;
    listaUsuarios = ControladorU->ObtenerUsuarios();
    if (listaUsuarios->isEmpty())
    {
        std::cout<< "N/A" << std::endl;
        pausa("Presione para continuar...");
        return;
    }else 
    {
        IIterator * ite;
        for (ite = listaUsuarios->getIterator(); ite->hasCurrent(); ite->next())
        {
            if (e = dynamic_cast<Estudiante*>(ite->getCurrent()))
            {
                std::cout << "Nickname del estudiante: " << e->getNickname() << std::endl;
            }
            
        }
        delete ite;

    }
    std::cout << std::endl;
    nickname = pedirString("el nombre del estudiante que desea inscribir en un curso");

    //cursosHabilitdos -> Esto guarda los cursos a los que el estudiante se puede inscribir (No esta inscripto, curso habilitado y tiene previas aprobadas)
    IDictionary * cursosHabilitados = new OrderedDictionary();

   cursosHabilitados = ControladorU->ListarCursosHabiEstudiantes(nickname);
    if(cursosHabilitados == nullptr){
        std::cout << "El estudiante: " << nickname << " no tiene cursos disponibles para inscribirse" << std::endl;
        pausa("Presione enter para continuar...");
        return;
    }

    DataCursoHab * dcurso;

    Estudiante* estudiante = ControladorU->ObtenerEstudiante(nickname);
    if (!estudiante) {
        std::cout << "El estudiante no existe" << std::endl;
        pausa("presione enter");
        //delete listaest;
        return;
    }
    

    IIterator * itc = cursosHabilitados->getIterator();

    std::cout << "-----------------------------------------------------------------------" << std::endl;
    while(itc->hasCurrent()){
        dcurso = dynamic_cast<DataCursoHab*>(itc->getCurrent());
        if(dcurso != nullptr){
            std::cout << std::endl;
            std::cout << "NombreCurso: " << dcurso->getNombreCurso() << std::endl;
            std::cout << "Descripcion del Curso: " << dcurso->getDescripcionCurso() << std::endl;
            std::cout << "Dificultad: " << obtenerTipoDificultad(dcurso->getDificultad()) << std::endl;
            std::cout << "Habilitado: " << ObtenerBool(dcurso->getHabilitado()) << std::endl;
            std::cout << "Cantidad de Lecciones del curso: " << dcurso->getLecciones()->getSize();

            int cantEjercicio = 0;
            IIterator * itl = dcurso->getLecciones()->getIterator();
            while(itl->hasCurrent()){
                DataLeccion * leccion = dynamic_cast<DataLeccion*>(itl->getCurrent());
                if(leccion != nullptr){
                    cantEjercicio += leccion->getEjerciciosLeccion()->getSize();
                }
                itl->next();
            }
            delete itl;
            std::cout << std::endl;
            std::cout << "Cantidad de ejercicios del Curso: " << cantEjercicio << std::endl;
            std::cout << "-----------------------------------------------------------------------" << std::endl;
        }
        itc->next();
    }
    delete itc;

    std::cout << std::endl;

    std::string seleccionarCurso = pedirString("el curso al que desea realizar una inscripcion");

    Date fecha = ObtenerFechaActual();

    ControladorU->InscribirCurso(nickname, seleccionarCurso, fecha);

    pausa("Presione enter para continuar");

}

//************************************************************************************//
//12
void RealizarEjercicio() {
    
 system("clear");
    printTitleInBox("Realizar Ejercicio");
    std::string nicknameuser;
    std::string Nomcurso;
    std::string SolucionIngresada;
    int Numejercicio;
    IDictionary* listacursos = new OrderedDictionary();
    IDictionary* listaUsuarios = new OrderedDictionary();
    IDictionary* EjerciciosNoAprobados = new OrderedDictionary();
    Estudiante* e = nullptr;
    Ejercicio* EJE = nullptr;
    Curso* c = nullptr;

    listaUsuarios = ControladorU->ObtenerUsuarios(); //muestra el nickname estudiantes
    if(listaUsuarios->isEmpty()){
        std::cout << "N/A" << std::endl;
        pausa("Presione enter para continuar...");
        return;
    }else{
        IIterator* ite;
        for(ite = listaUsuarios->getIterator(); ite->hasCurrent(); ite->next()){
            if(e = dynamic_cast<Estudiante*>(ite->getCurrent())){
                std::cout << "Nickname del estudiante: " << e->getNickname() << std::endl;
            }
        }
        delete ite;
        
    }
    std::cout << std::endl;
    nicknameuser = pedirString("el nickname del usuario para mostrar su informacion");

    e = ControladorU->ObtenerEstudiante(nicknameuser);
    if(!e){
        std::cout << "No se encontro el estudiante" << std::endl;
        pausa("Presione enter para continuar...");
        return;
    }

    listacursos = ControladorU->ListarCursosInscriptoNoAprobados(nicknameuser);
    std::cout << "Lista de Cursos no aprobados" << std::endl;
    //std::cout << "tamanio: " << listacursos->getSize();
    if(listacursos->isEmpty()){
        std::cout << "No tiene cursos no aprobados" << std::endl;
        pausa("Presione enter para continuar...");
        return;
    }else{
        IIterator* iter;
        for(iter = listacursos->getIterator(); iter->hasCurrent(); iter->next()){
            c = dynamic_cast<Curso*>(iter->getCurrent());
            std::cout << "Nombre Curso: " << c->getNombreCurso() << std::endl;
        }
        delete iter;
        std::cout << std::endl;
    }

    Nomcurso = pedirString("el nombre de Curso a seleccionar");

    EjerciciosNoAprobados = ControladorC->ListarEjerciciosNoAprobadosDeLeccion(Nomcurso, nicknameuser);

    Curso* curso = ControladorC->ObtenerCurso(Nomcurso);
    if(!curso){
        std::cout << "No existe curso con nombre: " << Nomcurso << std::endl;
        pausa("Presione enter para continuar...");
        return;
    }

    Registro* registro = e->getRegistro(Nomcurso);
    if(!registro){
        std::cout << "El estudiante no estra inscripto en el curso" << std::endl;
        pausa("Presione enter para continuar");
        return;
    }

    std::cout << "Lista de Ejercicios no aprobados de la ultima lección" << std::endl;
    if(EjerciciosNoAprobados->isEmpty()){
        std::cout << "N/A" << std::endl;
        pausa("Presione enter para continuar...");
        return;
    }else{
        IIterator* ite;
        for(ite = EjerciciosNoAprobados->getIterator(); ite->hasCurrent(); ite->next()){
            if(EJE = dynamic_cast<Ejercicio*>(ite->getCurrent())){
                CompletarPalabras* Completar = dynamic_cast<CompletarPalabras*>(EJE);
                Traduccion* Traducir = dynamic_cast<Traduccion*>(EJE);
                if(Completar){
                    std::cout << "Ejercicio de tipo Completar palabra" << std::endl;
                    std::cout << "Numero de ejercicio:  " << EJE->getContador() << std::endl;
                    std::cout << "Descripcion del ejercicio:  " << EJE->getDescripcion() << std::endl;
                    std::cout << std::endl;
                }else if(Traducir){
                    std::cout << "Ejercicio de tipo Traduccion" << std::endl;
                    std::cout << "Numero de ejercicio:  " << EJE->getContador() << std::endl;
                    std::cout << "Descripcion del ejercicio:  " << EJE->getDescripcion() << std::endl;
                    std::cout << std::endl;
                }
            }
        }
        delete ite;
        std::cout << std::endl;
    }
    Numejercicio = pedirInt("numero de ejercicio");
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    Leccion* leccion = curso->ultimaLeccionNoAprobada(e, Nomcurso);
    

    IIterator* ITEjercicio = EjerciciosNoAprobados->getIterator();
    while (ITEjercicio->hasCurrent()) {
        Ejercicio* Eje2 = dynamic_cast<Ejercicio*>(ITEjercicio->getCurrent());
        if(Eje2 && Eje2->getContador() == Numejercicio){
            CompletarPalabras* Completar = dynamic_cast<CompletarPalabras*>(Eje2);
            Traduccion* Traducir = dynamic_cast<Traduccion*>(Eje2);
            if(Completar){
                std::cout << "Ejercicio de tipo Completar palabra" << std::endl;
                std::cout << "Numero de ejercicio:  " << Eje2->getContador() << std::endl;
                std::cout << "Descripcion del ejercicio:  " << Eje2->getDescripcion() << std::endl;
                std::cout << "Frase:  " << Eje2->getFrase() << std::endl;
                std::cout << std::endl;
                SolucionIngresada =  pedirString("solucion ");
                bool ok = ControladorC->VerificarsolucionCompletarPlabra(Completar, SolucionIngresada);
                if(ok){
                    std::cout << "La solucion ingresada es correcta." << std::endl;
                    registro->agregarEjercicioAprobado(Eje2);
                    

                    bool todosAprobados = true;
                    IIterator* itLeccion = leccion->getEjerciciosLeccion()->getIterator();
                    while (itLeccion->hasCurrent()) {
                        Ejercicio* ejercicioLeccion = dynamic_cast<Ejercicio*>(itLeccion->getCurrent());
                        if (!registro->esEjercicioAprobado(ejercicioLeccion)) {
                            todosAprobados = false;
                            break;
                        }
                        itLeccion->next();
                    }
                    delete itLeccion;

                    if (todosAprobados) {
                        leccion->setAprobada(true);
                        registro->agregarLeccionAprobada(leccion);
    
                        std::cout << "Todos los ejercicios de la lección están aprobados. La lección ha sido marcada como aprobada." << std::endl;
                    } else {
                        std::cout << "Faltan ejercicios por aprobar." << std::endl;
                    }

                } else {
                    std::cout << "La solucion ingresada es incorrecta." << std::endl;
                }
            }else if(Traducir){
                std::cout << "Ejercicio de tipo Traduccion" << std::endl;
                std::cout << "Numero de ejercicio:  " << Eje2->getContador() << std::endl;
                std::cout << "Descripcion del ejercicio:  " << Eje2->getDescripcion() << std::endl;
                std::cout << "Frase:  " << Eje2->getFrase() << std::endl;
                std::cout << std::endl;
                SolucionIngresada =  pedirString("solucion ");
                bool ok = ControladorC->Verificarsoluciontraduccion(Traducir, SolucionIngresada);
                if(ok){
                    std::cout << "La solucion ingresada es correcta." << std::endl;
                    registro->agregarEjercicioAprobado(Eje2);
                    
                    bool todosAprobados = true;
                    IIterator* itLeccion = leccion->getEjerciciosLeccion()->getIterator();
                    while (itLeccion->hasCurrent()) {
                        Ejercicio* ejercicioLeccion = dynamic_cast<Ejercicio*>(itLeccion->getCurrent());
                        if (!registro->esEjercicioAprobado(ejercicioLeccion)) {
                            todosAprobados = false;
                            break;
                        }
                        itLeccion->next();
                    }
                    delete itLeccion;

                    if (todosAprobados) {
                        leccion->setAprobada(true);
                        registro->agregarLeccionAprobada(leccion);
                        
                        std::cout << "Todos los ejercicios de la lección están aprobados. La lección ha sido marcada como aprobada." << std::endl;
                    } else {
                        std::cout << "Faltan ejercicios por aprobar." << std::endl;
                    }

                } else {
                    std::cout << "La solucion ingresada es incorrecta." << std::endl;
                }
            }
            break;
        }
        ITEjercicio->next();
    }
    delete ITEjercicio;

    double porcentaje = ControladorC->CalcularporcentajeAprobacion(nicknameuser, Nomcurso);
    std::cout << "Porcentaje Avance: " << porcentaje << std::endl;
    pausa("Presione enter para continuar");
}


//************************************************************************************//
//13
void ConsultarEstadisticas(){
    std::string nickname;
    std::string nombrecurso;
    
    

    system("clear");
    printTitleInBox("Consultar Estadisticas");

    int opcion;
    
    std::cout << "1 - Consultar Estadisticas del Estudiante" << std::endl;
    std::cout << "2 - Consultar Estadisticas del Profesor" << std::endl;
    std::cout << "3 - Consultar Estadisticas del Curso" << std::endl;
    opcion = obteneropcion2();

    Estudiante * est;
    IDictionary * auxlist = new OrderedDictionary();
    IDictionary * estadisticas = new OrderedDictionary();
    IIterator * itl;
    IIterator * itc;
    //COnsultar profesores
    IDictionary * listaprofes = new OrderedDictionary();
    IDictionary* estadisticasp = new OrderedDictionary();
    IIterator * itp;
    bool valido;
    Profesor * profe;
    //curso
    Curso * curso;
    IDictionary * estadisticascurso = new OrderedDictionary();
    IDictionary * auxlistcurso = new OrderedDictionary();
    IIterator * itc2;
    DataEstadisticaCurso * dataCurso;
    IIterator * itpp;
    switch(opcion){
        case 1:
            system("clear");
            printTitleInBox("Consultar Estadisticas del Estudiante");
            std::cout << "Lista de estudiantes: " << std::endl;
            std::cout << std::endl;
            auxlist = ControladorU->ListarEstudiantes();
            if(auxlist->isEmpty()){
                std::cout << "No hay estudiantes ingresados todavia" << std::endl;
                pausa("Presione enter para continuar...");
                return;
            }else{
                for(itl = auxlist->getIterator(); itl->hasCurrent(); itl->next()){
                    Estudiante * estudiante = dynamic_cast<Estudiante*>(itl->getCurrent());
                    std::cout << "Nickname Estudiante: " << estudiante->getNickname() << std::endl;
                }
                delete itl;
            }
            std::cout << std::endl;
            nickname = pedirString("el nickname del estudiante al que quiere consultar sus estadisticas");
            est = ControladorU->ObtenerEstudiante(nickname);
            if(!est){
                std::cout << "Estudiante no existe" << std::endl;
                pausa("Presione enter para continuar...");
                return;
            }
            estadisticas = ControladorU->ConsultarEstadisticasEstudiante(nickname);

            if (estadisticas->isEmpty()) {
            std::cout << "El estudiante no está inscrito en ningún curso" << std::endl;
        } else {
            IIterator* it = estadisticas->getIterator();
            while (it->hasCurrent()) {
                CursoEstadistica* cursoEstadistica = dynamic_cast<CursoEstadistica*>(it->getCurrent());
                Curso* curso = cursoEstadistica->curso;
                double porcentajeAvance = cursoEstadistica->porcentajeAvance;
                int ejap = cursoEstadistica->ejerciciosAprobados;
                std::cout << std::endl;
                std::cout << "Nombre del Curso: " << curso->getNombreCurso() << std::endl;
                std::cout << "Descripcion del Curso: " << curso->getDescripcionCurso() << std::endl;
                std::cout << "Dificultad del Curso: " << obtenerTipoDificultad(curso->getDificultad())  << std::endl;
                std::cout << "Porcentaje de Avance: " << porcentajeAvance << "%" << std::endl;
                std::cout << "Ejercicios Aprobados: " << ejap << std::endl;
                it->next();
            }
            delete it;
        }
            break;
        case 2:
                
            system("clear");
            printTitleInBox("Consultar Estadisticas del Profesor");

            std::cout << "NO IMPLEMENTADO" << std::endl;

            break;
        case 3:
            system("clear");
            printTitleInBox("Consultar Estadisticas del Curso");

            auxlistcurso = ControladorC->ListarCursos();
            if(auxlistcurso->isEmpty()){
                std::cout << "N/A" << std::endl;
            }else{
                IIterator * iti;
                 for(iti = auxlistcurso->getIterator(); iti->hasCurrent(); iti->next()){
                    Curso * i = dynamic_cast<Curso*>(iti->getCurrent());
                    std::cout << "Nombre curso: " <<  i->getNombreCurso() << std::endl;
                }
            }
            std::cout << std::endl;
            nombrecurso = pedirString("el nombre del curso al que quiere consultar sus estadisticas");
            curso = ControladorC->ObtenerCurso(nombrecurso);
            if(!curso){
                std::cout << "El curso ingresado no existe " << std::endl;
                pausa("Presione enter para continuar...");
                return;
            }
            std::cout << std::endl;
            dataCurso = dynamic_cast<DataEstadisticaCurso*>(ControladorC->consultarEstadisticasCurso(nombrecurso));
            if (estadisticascurso != nullptr) {
                std::cout << "Nombre del curso: " << dataCurso->getNombreCurso() << std::endl;
                std::cout << "Descripcion del curso: " << dataCurso->getDescripcion() << std::endl;
                std::cout << "Dificultad del curso: " << obtenerTipoDificultad(dataCurso->getDificultadCurso())  << std::endl;
                std::cout << "Promedio de avance de estudiantes en el curso: " << dataCurso->getPromedioAvance() << "%" << std::endl;
                //delete estadisticascurso;
            }
            
            break;
        default:
            std::cout << "Opcion ingresada invalida" << std::endl;
            break;
        }
    pausa("Presione enter para continuar...");
  
}

//************************************************************************************//
//14
void CargarDatos(){
    system("clear");
    //////////USUARIO////////////
    std::string nicknameuser;
    std::string nombreuser;
    std::string descripcionuser;
    std::string contraseniauser;
    std::string pais;
    Date fechaNac;
    std::string instituto;
    //////////USUARIO////////////

    //////////IDIOMA////////////
    std::string idioma;
    //////////IDIOMA////////////

    ////////Inscripcion/////////
    int dia,mes,anio;
    Date FechaIns;



    std::cin.clear();
    int opcion;
    printTitleInBox("Pre-Cargar Datos");
    Profesor * profesor;
    Curso * curso;
    

    idiomashandler->AltaIdioma("aleman");
    idiomashandler->AltaIdioma("ingles");
    idiomashandler->AltaIdioma("portugues");

    //Estudiante
    nicknameuser = "jpidiom"; //U1 - done
    nombreuser = "Juan Perez";
    descripcionuser = "Soy un apasionado del aprendizaje de idiomas.";
    contraseniauser = "123456";
    pais = "Argentina";
    fechaNac = Date(15, 7, 1995);
    ControladorU->ConfirmarAltaEstudiante(nicknameuser, nombreuser, descripcionuser,contraseniauser,pais,fechaNac);
    nicknameuser.clear(); descripcionuser.clear(); contraseniauser.clear(); pais.clear();

    nicknameuser = "marsilva"; //U2 - done
    nombreuser = "Maria Silva";
    descripcionuser = "Como amante de los idiomas disfruto explorando nuevas formas de interactuar.";
    contraseniauser = "123456";
    pais = "Ecuador";
    fechaNac = Date(28, 2, 1998);
    ControladorU->ConfirmarAltaEstudiante(nicknameuser, nombreuser, descripcionuser,contraseniauser,pais,fechaNac);
    nicknameuser.clear(); descripcionuser.clear(); contraseniauser.clear(); pais.clear();

    nicknameuser = "pero12"; //U3 - done
    nombreuser = "Pedro Rodriguez";
    descripcionuser = "Soy un entusiasta del aprendizaje de idiomas.";
    contraseniauser = "123456";
    pais = "Peru";
    fechaNac = Date(10, 11, 1994);
    ControladorU->ConfirmarAltaEstudiante(nicknameuser, nombreuser, descripcionuser,contraseniauser,pais,fechaNac);
    nicknameuser.clear(); descripcionuser.clear(); contraseniauser.clear(); pais.clear();

    nicknameuser = "laugu";//U4 - done
    nombreuser = "Laura Gutierrez";
    descripcionuser = "Estoy fascinada por la forma en que las palabras pueden unir a las personas";
    contraseniauser = "123456";
    pais = "Chile";
    fechaNac = Date(22, 4, 1997);
    ControladorU->ConfirmarAltaEstudiante(nicknameuser, nombreuser, descripcionuser,contraseniauser,pais,fechaNac);
    nicknameuser.clear(); descripcionuser.clear(); contraseniauser.clear(); pais.clear();

    nicknameuser = "carlo22"; //U5 - done
    nombreuser = "Carlos Lopez";
    descripcionuser = "Emocionado por adquirir fluidez en diferentes lenguas.";
    contraseniauser = "123456";
    pais = "Uruguay";
    fechaNac = Date(3, 9, 1996);
    ControladorU->ConfirmarAltaEstudiante(nicknameuser, nombreuser, descripcionuser,contraseniauser,pais,fechaNac);
    nicknameuser.clear(); descripcionuser.clear(); contraseniauser.clear(); pais.clear();

    nicknameuser = "anator"; //U6 - done
    nombreuser = "Ana Torres";
    descripcionuser = "Disfruto de la belleza de las diferentes estructuras y sonidos.";
    contraseniauser = "123456";
    pais = "Argentina";
    fechaNac = Date(12, 1, 1999);
    ControladorU->ConfirmarAltaEstudiante(nicknameuser, nombreuser, descripcionuser,contraseniauser,pais,fechaNac);
    nicknameuser.clear(); descripcionuser.clear(); contraseniauser.clear(); pais.clear();

    nicknameuser = "luher24"; //U7 - done
    nombreuser = "Lucia Hernandez";
    descripcionuser = "Emocionada en la riqueza cultural que cada idioma ofrece.";
    contraseniauser = "123456";
    pais = "Colombia";
    fechaNac = Date(25, 6, 1993);
    ControladorU->ConfirmarAltaEstudiante(nicknameuser, nombreuser, descripcionuser,contraseniauser,pais,fechaNac);
    nicknameuser.clear(); descripcionuser.clear(); contraseniauser.clear(); pais.clear();

    nicknameuser = "dagon"; //U8 - done
    nombreuser = "David Gonzalez";
    descripcionuser = "Aprender nuevas lenguas y sumergirme en diferentes culturas.";
    contraseniauser = "123456";
    pais = "Uruguay";
    fechaNac = Date(8, 12, 1997);
    ControladorU->ConfirmarAltaEstudiante(nicknameuser, nombreuser, descripcionuser,contraseniauser,pais,fechaNac);
    nicknameuser.clear(); descripcionuser.clear(); contraseniauser.clear(); pais.clear();

    nicknameuser = "carmor"; //U9 - done
    nombreuser = "Carmen Morales";
    descripcionuser = "El aprendizaje de idiomas y expandir mis habilidades comunicativas en diferentes lenguas.";
    contraseniauser = "123456";
    pais = "Chile";
    fechaNac = Date(17, 3, 1995);
    ControladorU->ConfirmarAltaEstudiante(nicknameuser, nombreuser, descripcionuser,contraseniauser,pais,fechaNac);
    nicknameuser.clear(); descripcionuser.clear(); contraseniauser.clear(); pais.clear();

    nicknameuser = "jose24"; //U10 - done
    nombreuser = "Jose Fernandez";
    descripcionuser = "Disfruto del proceso de descubrir nuevas formas de comunicarme";
    contraseniauser = "123456";
    pais = "Bolivia";
    fechaNac = Date(2, 8, 1998);
    ControladorU->ConfirmarAltaEstudiante(nicknameuser, nombreuser, descripcionuser,contraseniauser,pais,fechaNac);
    nicknameuser.clear(); descripcionuser.clear(); contraseniauser.clear(); pais.clear();


    //profesor

    nicknameuser = "langmaster"; //U11 - done
    nombreuser = "Marta Grecia";
    descripcionuser = "Soy una profesora apasionada por los idiomas.";
    contraseniauser = "123456";
    instituto = "Instituto de Idiomas Moderno";
    ControladorU->ConfirmarAltaProfesor(nicknameuser,nombreuser, descripcionuser, contraseniauser, instituto);
    profesor = ControladorU->ObtenerProfesor(nicknameuser);
    ControladorU->SetProfesorActual(profesor);
    ControladorU->AgregarIdioma("ingles");
    ControladorU->AgregarIdioma("portugues");
    nicknameuser.clear(); descripcionuser.clear(); contraseniauser.clear(); instituto.clear();

    nicknameuser = "linguapro"; //U12 - done
    nombreuser = "Carlos Petro";
    descripcionuser = "Mi objetivo es inspirar a mis estudiantes a explorar nuevas culturas e idiomas";
    contraseniauser = "123456";
    instituto = "Centro Global";
    ControladorU->ConfirmarAltaProfesor(nicknameuser,nombreuser, descripcionuser, contraseniauser, instituto);
    profesor = ControladorU->ObtenerProfesor(nicknameuser);
    ControladorU->SetProfesorActual(profesor);
    ControladorU->AgregarIdioma("ingles");
    ControladorU->AgregarIdioma("portugues");
    ControladorU->AgregarIdioma("aleman");
    nicknameuser.clear(); descripcionuser.clear(); contraseniauser.clear(); instituto.clear();

    nicknameuser = "talkexpert"; //U13 - done
    nombreuser = "Laura Perez";
    descripcionuser = "Soy una profesora entusiasta del aprendizaje de idiomas";
    contraseniauser = "123456";
    instituto = "Instituto de Idiomas Vanguardia";
    ControladorU->ConfirmarAltaProfesor(nicknameuser,nombreuser, descripcionuser, contraseniauser, instituto);
    profesor = ControladorU->ObtenerProfesor(nicknameuser);
    ControladorU->SetProfesorActual(profesor);
    ControladorU->AgregarIdioma("aleman");
    nicknameuser.clear(); descripcionuser.clear(); contraseniauser.clear(); instituto.clear();

    nicknameuser = "lingosensei"; //U14 - done
    nombreuser = "Franco Lopez";
    descripcionuser = "Apasionada en guiar a mis estudiantes en su viaje por nuevos horizontes idiomaticos";
    contraseniauser = "123456";
    instituto = "Centro de Idiomas";
    ControladorU->ConfirmarAltaProfesor(nicknameuser,nombreuser, descripcionuser, contraseniauser, instituto);
    profesor = ControladorU->ObtenerProfesor(nicknameuser);
    ControladorU->SetProfesorActual(profesor);
    ControladorU->AgregarIdioma("portugues");
    nicknameuser.clear(); descripcionuser.clear(); contraseniauser.clear(); instituto.clear();

    nicknameuser = "wordmaestro"; //U15 - done
    nombreuser = "Ana Morales";
    descripcionuser = "Soy una profesora comprometida en desarrollo de habilidades idiomaticas";
    contraseniauser = "123456";
    instituto = "Instituto de Idiomas Progreso";
    ControladorU->ConfirmarAltaProfesor(nicknameuser,nombreuser, descripcionuser, contraseniauser, instituto);
    profesor = ControladorU->ObtenerProfesor(nicknameuser);
    ControladorU->SetProfesorActual(profesor);
    ControladorU->AgregarIdioma("ingles");
    nicknameuser.clear(); descripcionuser.clear(); contraseniauser.clear(); instituto.clear();

    //Cursos
    Curso * p1;
    Curso * p2;

    //c1 - done
    ControladorC->IngresarCurso("langmaster", "ingles para principiantes", "Curso para personas con poco o ningn conocimiento de ingles. Se enfoca en vocabulario basico, gramatica y habilidades de conversacion.", Principiante);
    curso = ControladorC->ObtenerCurso("ingles para principiantes");
    ControladorC->setCursoActual(curso);
    ControladorC->AgregarIdiomaCurso("ingles");
    //esto va habilitado
    curso->setHabilitado(true);//no va aca

    //c2 - done
    ControladorC->IngresarCurso("langmaster", "curso de ingles basico", "Construye unabase solida en el idioma. Cubre gramatica, vocabulario, comprension auditiva y expresion oral", Principiante);
    curso = ControladorC->ObtenerCurso("curso de ingles basico");
    ControladorC->setCursoActual(curso);
    ControladorC->AgregarIdiomaCurso("ingles");
    //no habilitado
    
    //c3 - done
    ControladorC->IngresarCurso("linguapro", "ingles intermedio: mejora tu nivel", "Para estudiantes con conocimientos basicos de ingles que desean avanzar en su habilidad comunicativa. Se centra en la fluidez oral, lectura comprensiva y escritura", Medio);
    curso = ControladorC->ObtenerCurso("ingles intermedio: mejora tu nivel");
    ControladorC->setCursoActual(curso);
    ControladorC->AgregarIdiomaCurso("ingles");
    //esto va habilitado
    curso->setHabilitado(true);//no va aca
std::cout << "Muere aca 4" << std::endl;
    //agregar cursos previos al curso
    p1 = ControladorC->ObtenerCurso("ingles para principiantes");
    //ControladorC->setCursoActual(curso);
    curso->AgregarCursoPrevioCurso(p1);
    
    //c4 - done
    ControladorC->IngresarCurso("linguapro", "curso avanzado de ingles", "Dirigido a personas con un nivel intermiedo-alto que desean perfeccionar sus habilidades en todos los aspectos dle idioma. Incliye gramatica avanzada, vocabulario y comprension escrita y auditiva", Avanzado);
    curso = ControladorC->ObtenerCurso("curso avanzado de ingles");
    ControladorC->setCursoActual(curso);
    ControladorC->AgregarIdiomaCurso("ingles");
    //esto va habilitado
    curso->setHabilitado(true);//no va aca
    std::cout << "Muere aca 2" << std::endl;
    //agregar cursos previos al curso
    p1 = ControladorC->ObtenerCurso("ingles para principiantes");
    //ControladorC->setCursoActual(curso);
    curso->AgregarCursoPrevioCurso(p1);
    std::cout << "Muere aca 3" << std::endl;
    p2 = ControladorC->ObtenerCurso("ingles intermedio: mejora tu nivel");
    //ControladorC->setCursoActual(curso);
    curso->AgregarCursoPrevioCurso(p2);
    std::cout << "cant cursos previos curso avnzado de ingles " << curso->getCursosPreviosCurso()->getSize() << std::endl;

    //c5 - done
    ControladorC->IngresarCurso("linguapro", "portugues intermedio", "Curso para aquellos que tienen conocimientos basicos de portugues y desean mejorar su nivel. Incluye practica de lectura, escritura y comprensiona auditiva.", Medio);
    curso = ControladorC->ObtenerCurso("portugues intermedio");
    ControladorC->setCursoActual(curso);
    ControladorC->AgregarIdiomaCurso("portugues");
    //esto va habilitado
    curso->setHabilitado(true); //no va acaS
    
    //c6 - done
    ControladorC->IngresarCurso("lingosensei", "portugues avanzado", "Curso avanzado para personas con un nivel intermedio-alto de portugues que desean perfeccionar su fluidez y dominio del idioma. Se trabaja en la gramatica avanzada y la expresion oral.", Avanzado);
    curso = ControladorC->ObtenerCurso("portugues avanzado");
    ControladorC->setCursoActual(curso);
    ControladorC->AgregarIdiomaCurso("portugues");
    //no habilitado
    std::cout << "Muere aca 1" << std::endl;
    //agregar cursos previos al curso 
    p1 = ControladorC->ObtenerCurso("portugues intermedio");
    //ControladorC->setCursoActual(curso);
    curso->AgregarCursoPrevioCurso(p1);

    //Lecciones
    //L1
    ControladorC->AgregarLeccion("saludos y presentaciones", "Aprender a saludar y despedirse", "ingles para principiantes");
    //L2
    ControladorC->AgregarLeccion("articulos y plurales", "Comprender y utilizar los articulos definidos e indefinidos, Aprender a formar los plurales regulares e irregulares de sustantivos", "ingles para principiantes");
    //L3
    ControladorC->AgregarLeccion("actividades cotidianas", "Comprender y utilizar los articulos definidos e indefinidos, Aprender a formar los plurales regulares e irregulares de sustantivos", "curso de ingles basico");
    //L4
    ControladorC->AgregarLeccion("presente simple", "Aprender el uso del presente simple", "curso de ingles basico");
    //L5
    ControladorC->AgregarLeccion("conversaciones cotidianas", "Aprender a hacer preguntas y respuestas en situaciones comunes", "ingles intermedio: mejora tu nivel");
    //L6
    ControladorC->AgregarLeccion("uso de modales avanzados", "Explorar el uso de los modales complejos","curso avanzado de ingles");
    //L7
    ControladorC->AgregarLeccion("lectura y comprension de textos", "Analizar el contenido, vocabulario y estructuras gramaticales utilizadas", "portugues intermedio");

    //Ejercicios
    //E1 L1 C1
    ControladorC->AgregarEjercicioTraduccion("ingles para principiantes", "saludos y presentaciones", "Mucho gusto en conocerte", "presentaciones", "nice to meet you");
    //E2 L1 C1
    ControladorC->AgregarEjercicioCompletarPalabras("ingles para principiantes", "saludos y presentaciones", "please --- me to introduce ---","presentaciones formales", "allow, myself");
    //E3 L2 C1
    ControladorC->AgregarEjercicioTraduccion("ingles para principiantes", "articulos y plurales", "i have two brothers and three sisters", "plurales regulares", "tengo dos hermanos y tres hermanas");
    //E4 L2 C1
    ControladorC->AgregarEjercicioCompletarPalabras("ingles para principiantes", "articulos y plurales", "can i have --- water, please?", "sustantivos contables en plural", "some");
    //E5 L3 C2
    ControladorC->AgregarEjercicioCompletarPalabras("curso de ingles basico", "actividades cotidianas", "wake ---", "actividades diarias", "up");
    //E6 L5 C3
    ControladorC->AgregarEjercicioCompletarPalabras("ingles intermedio: mejora tu nivel", "conversaciones cotidianas", "q: do you --- the time?, a: yes, it is half --- 4", "consultas de la hora", "have, past");
    //E7 L6 C4
    ControladorC->AgregarEjercicioTraduccion("curso avanzado de ingles", "uso de modales avanzados", "you should visit that museum", "dar consejos o expresar obligacion", "deberias visitar ese museo");
    //E8 L7 C5
    ControladorC->AgregarEjercicioTraduccion("portugues intermedio", "lectura y comprension de textos", "fale comigo", "imperativo", "habla conmigo");

    //Inscripciones
    //U1 C1
    dia = 1;
    mes = 1;
    anio = 2022;
    FechaIns = Date(dia,mes,anio);
    ControladorU->InscribirCurso("jpidiom","ingles para principiantes",FechaIns);

    //Ejercicios aprobados y leccion aprobada
        //EjerciciosAprobados
    //N1 - done

    ControladorU->CargarAprobado("jpidiom", "ingles para principiantes", "saludos y presentaciones", "presentaciones");
    ControladorU->CargarAprobado("jpidiom", "ingles para principiantes", "saludos y presentaciones", "presentaciones formales");
    ControladorU->CargarAprobado("jpidiom", "ingles para principiantes", "articulos y plurales", "plurales regulares");
    ControladorU->CargarAprobado("jpidiom", "ingles para principiantes", "articulos y plurales", "sustantivos contables en plural");

    Estudiante * e = ControladorU->ObtenerEstudiante("jpidiom");

    Registro * reg = e->getRegistro("ingles para principiantes");

    curso = ControladorC->ObtenerCurso("ingles para principiantes");
    Leccion * lec = curso->ObtenerLeccion("saludos y presentaciones");
    Ejercicio * ej = lec->ObtenerEjercicio("presentaciones");
    ej->setAprobado(true);
    reg->agregarEjercicioAprobado(ej);


    lec = curso->ObtenerLeccion("saludos y presentaciones");
    ej = lec->ObtenerEjercicio("presentaciones formales");
    ej->setAprobado(true);
    reg->agregarEjercicioAprobado(ej);
    
    lec->setAprobada(true);
    reg->agregarLeccionAprobada(lec);

    lec = curso->ObtenerLeccion("articulos y plurales");
    ej = lec->ObtenerEjercicio("plurales regulares");
    ej->setAprobado(true);
    reg->agregarEjercicioAprobado(ej);

    lec = curso->ObtenerLeccion("articulos y plurales");
    ej = lec->ObtenerEjercicio("sustantivos contables en plural");
    ej->setAprobado(true);
    reg->agregarEjercicioAprobado(ej);

    lec->setAprobada(true);
    reg->agregarLeccionAprobada(lec);

    double porcentaje;
    porcentaje = ControladorC->CalcularporcentajeAprobacion("jpidiom", "ingles para principiantes");

    
    //U1 C3
    dia = 12;
    mes = 6;
    anio = 2022;
    FechaIns = Date(dia,mes,anio);
    ControladorU->InscribirCurso("jpidiom","ingles intermedio: mejora tu nivel",FechaIns);

    //N2 - done
    ControladorU->CargarAprobado("jpidiom", "ingles intermedio: mejora tu nivel", "conversaciones cotidianas", "consultas de la hora");
    reg = e->getRegistro("ingles intermedio: mejora tu nivel");
    curso = ControladorC->ObtenerCurso("ingles intermedio: mejora tu nivel");
    lec = curso->ObtenerLeccion("conversaciones cotidianas");
    ej = lec->ObtenerEjercicio("consultas de la hora");
    ej->setAprobado(true);
    reg->agregarEjercicioAprobado(ej);
    lec->setAprobada(true);
    reg->agregarLeccionAprobada(lec);

    porcentaje = ControladorC->CalcularporcentajeAprobacion("jpidiom", "ingles intermedio: mejora tu nivel");

    //U1 C4
    dia = 2;
    mes = 3;
    anio = 2023;
    FechaIns = Date(dia,mes,anio);
    ControladorU->InscribirCurso("jpidiom","curso avanzado de ingles",FechaIns);


    //U2 C1
    dia = 2;
    mes = 1;
    anio = 2022;
    FechaIns = Date(dia,mes,anio);
    ControladorU->InscribirCurso("marsilva","ingles para principiantes",FechaIns);

    //N4 - U2 -C1 done
    ControladorU->CargarAprobado("marsilva", "ingles para principiantes", "saludos y presentaciones", "presentaciones");
    ControladorU->CargarAprobado("marsilva", "ingles para principiantes", "saludos y presentaciones", "presentaciones formales");

    e = ControladorU->ObtenerEstudiante("marsilva");
    reg = e->getRegistro("ingles para principiantes");
    curso = ControladorC->ObtenerCurso("ingles para principiantes");
    lec = curso->ObtenerLeccion("saludos y presentaciones");
    ej = lec->ObtenerEjercicio("presentaciones");
    ej->setAprobado(true);
    reg->agregarEjercicioAprobado(ej);

    ej = lec->ObtenerEjercicio("presentaciones formales");
    ej->setAprobado(true);
    reg->agregarEjercicioAprobado(ej);

    lec->setAprobada(true);
    reg->agregarLeccionAprobada(lec);

    porcentaje = ControladorC->CalcularporcentajeAprobacion("marsilva", "ingles para principiantes");

    //U3 C1
    dia = 2;
    mes = 1;
    anio = 2022;
    FechaIns = Date(dia,mes,anio);
    ControladorU->InscribirCurso("pero12","ingles para principiantes",FechaIns);

    //N5 - done
    ControladorU->CargarAprobado("pero12", "ingles para principiantes", "saludos y presentaciones", "presentaciones");
    ControladorU->CargarAprobado("pero12", "ingles para principiantes", "saludos y presentaciones", "presentaciones formales");
    ControladorU->CargarAprobado("pero12", "ingles para principiantes", "articulos y plurales", "sustantivos contables en plural");

    e = ControladorU->ObtenerEstudiante("pero12");
    reg = e->getRegistro("ingles para principiantes");
    curso = ControladorC->ObtenerCurso("ingles para principiantes");

    
    lec = curso->ObtenerLeccion("saludos y presentaciones");
    ej = lec->ObtenerEjercicio("presentaciones");
    ej->setAprobado(true);
    reg->agregarEjercicioAprobado(ej);

 

    ej = lec->ObtenerEjercicio("presentaciones formales");
    ej->setAprobado(true);
    reg->agregarEjercicioAprobado(ej);
    lec->setAprobada(true);
    reg->agregarLeccionAprobada(lec);

 
    lec = curso->ObtenerLeccion("articulos y plurales");
    ej = lec->ObtenerEjercicio("sustantivos contables en plural");
    ej->setAprobado(true);
    reg->agregarEjercicioAprobado(ej);

    porcentaje = ControladorC->CalcularporcentajeAprobacion("pero12", "ingles para principiantes");


    //U4 C1
    dia = 3;
    mes = 1;
    anio = 2023;
    FechaIns = Date(dia,mes,anio);
    ControladorU->InscribirCurso("laugu","ingles para principiantes",FechaIns);


    //U4 C5
    dia = 3;
    mes = 1;
    anio = 2023;
    FechaIns = Date(dia,mes,anio);
    ControladorU->InscribirCurso("laugu","portugues intermedio",FechaIns);


    //U5 C5
    dia = 5;
    mes = 1;
    anio = 2023;
    FechaIns = Date(dia,mes,anio);
    ControladorU->InscribirCurso("carlo22","portugues intermedio",FechaIns);

}

//************************************************************************************//
//15
void salirSistema() {
    std::cout << "Saliendo del sistema...\n";
    exit(0);
}



