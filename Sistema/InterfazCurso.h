#ifndef INTERFAZCURSO_H
#define INTERFAZCURSO_H

#include <iostream>
#include <string>
#include "../Datatypes/Enum.h"
#include "../Datatypes/Datatypes.h"
#include "Usuario/Profesor.h"
#include "Usuario/Estudiante.h"
#include "ControladorCurso.h"

class InterfazCurso{
    
    private:

    public:
        // 5 - Alta Curso
        virtual IDictionary * IngresarCurso(std::string nicknamep, std::string nombrec, std::string descripcionc, TipoDificultad dificultadc) = 0;
        virtual void AgregarIdiomaCurso(std::string nombreidioma) = 0;
        virtual void setCursoActual(Curso * curso) = 0;
        virtual Curso * ObtenerCurso(std::string nombrecurso) = 0;
        virtual IDictionary * ListarCursosHabilitados() = 0;
        virtual void AgregarCursoPrevio(std::string nombrecurso) = 0;
        virtual IDictionary * ListarCursosHabilitadosAprobados(std::string nickname) = 0;
        // 6 - Agregar Leccion
        virtual void AgregarLeccion(std::string tema, std::string objetivo, std::string nombrecurso) = 0;
        // 7 - Agregar Ejercicio
        virtual void AgregarEjercicioTraduccion(std::string nombrecurso, std::string temaleccion, std::string frase, std::string descripcion, std::string fraseCorrectaT) = 0;
        virtual void AgregarEjercicioCompletarPalabras(std::string nombrecurso, std::string temaleccion, std::string frase, std::string descripcion, std::string palabras) = 0;
        virtual bool ExisteLeccion(std::string nombrecurso, std::string tema) = 0;
        // 8 - Habilitar Curso
        virtual IDictionary * ListarCursosNoHabilitados() = 0;
        virtual void habilitar_curso(std::string Nombrecurso) =0;
        // 9 - Eliminar Curso
        virtual void EliminarCurso(std::string nombreCurso) = 0;
        // 10 - Consultar Curso
        virtual IDictionary* ListarCursos() = 0;
        virtual IDictionary* ListarLeccionesCurso(std::string nombrecurso) = 0;
        virtual IDictionary* ListarEjerciciosLecciones(std::string nombrecurso, std::string temaleccion) = 0;
        virtual IDictionary* ListarInscripciones(std::string nombrecurso) = 0;
        // 11 - Inscribirse a Curso
        virtual IDictionary * ListarDataCurso() = 0;
        // 12 - Realizar Ejercicio
        virtual IDictionary* ListarEjerciciosNoAprobadosDeLeccion(std::string Nombrecurso, std::string Nickname) = 0;
        virtual bool Verificarsoluciontraduccion(Traduccion* T, std::string SolucionIngresada) = 0;
        virtual bool VerificarsolucionCompletarPlabra(CompletarPalabras* CP, std::string SolucionIngresadaC) = 0;
        virtual double CalcularporcentajeAprobacion(std::string nicknameusuario, std::string nomcurso) = 0;
        // 13 - Consultar Estadisticas
        virtual DataEstadisticaCurso* consultarEstadisticasCurso(std::string nombreCurso) = 0;

};

#endif
