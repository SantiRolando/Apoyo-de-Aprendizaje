#ifndef CONTROLADORCURSO_H
#define CONTROLADORCURSO_H

#include "InterfazCurso.h"
#include "Curso/Ejercicio.h"
#include "HandlerIdioma.h"
#include "ControladorUsuario.h"
#include <string>
#include <sstream>
#include "../ico.h"
#include "../Datatypes/Enum.h"
#include "../Datatypes/DataProfesor.h"
#include "../Datatypes/DataEstudiante.h"
#include "Curso/Idioma.h"
#include "Curso/Leccion.h"

#include "Curso/CompletarPalabras.h"
#include "Curso/Traduccion.h"




class ControladorCurso: public InterfazCurso{

    private:
        static ControladorCurso *instance;
        ControladorCurso();
        
        int ejerciciosContador = 0;
        TipoDificultad Dificultad;
        std::string Descripcion;
        std::string NombreCurso;
        bool habilitado;

        IDictionary* cursos;

        //////
        Curso * cursoActual;
        //////

    public:
        static ControladorCurso* getInstance();
        // 5 - AltaCurso
        IDictionary * IngresarCurso(std::string nicknamep, std::string nombrec, std::string descripcionc, TipoDificultad dificultadc);
        void AgregarIdiomaCurso(std::string nombreidioma);
        void setCursoActual(Curso * curso);
        Curso * ObtenerCurso(std::string nombrecurso);
        IDictionary * ListarCursosHabilitados(); // retorna el nombre datacursohabmini
        void AgregarCursoPrevio(std::string nombrecurso);
        IDictionary * ListarCursosHabilitadosAprobados(std::string nickname);

        // 6 - AgregarLeccion
        void AgregarLeccion(std::string tema, std::string objetivo, std::string nombrecurso);
        // 7 - AgregarEjercicio
        void AgregarEjercicioTraduccion(std::string nombrecurso, std::string temaleccion, std::string frase, std::string descripcion, std::string fraseCorrectaT);
        void AgregarEjercicioCompletarPalabras(std::string nombrecurso, std::string temaleccion, std::string frase, std::string descripcion, std::string palabras);
        bool ExisteLeccion(std::string nombrecurso, std::string tema);
        // 8 - HabilitarCurso
        IDictionary * ListarCursosNoHabilitados(); //Retorna solo el nombre del curso datacursohabmini
        void habilitar_curso(std::string Nombrecurso);//habilita los cursos pasados por parametro, o avisa que no pueden ser habilitados
        // 9 - Eliminar Curso
        void EliminarCurso(std::string nombreCurso);
        // 10 - Consultar Cursos
        IDictionary* ListarCursos();
        IDictionary* ListarLeccionesCurso(std::string nombrecurso);
        IDictionary* ListarEjerciciosLecciones(std::string nombrecurso, std::string temaleccion);
        IDictionary* ListarInscripciones(std::string nombrecurso);
        // 11 - Inscribirse a Curso
        IDictionary * ListarDataCurso(); //para comentar
        // 12 - Realizar Ejercicio
        bool Verificarsoluciontraduccion(Traduccion* T, std::string SolucionIngresada);
        bool VerificarsolucionCompletarPlabra(CompletarPalabras* CP, std::string SolucionIngresadaC);
        double CalcularporcentajeAprobacion(std::string nicknameusuario, std::string nomcurso);
        IDictionary* ListarEjerciciosNoAprobadosDeLeccion(std::string Nombrecurso, std::string Nickname);
        // 13 - Consultar Estadisticas
        DataEstadisticaCurso* consultarEstadisticasCurso(std::string nombreCurso);

};

#endif