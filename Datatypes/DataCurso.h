#ifndef DATACURSO_H
#define DATACURSO_H

#include "../ico.h"
#include <string>
#include "Enum.h"

class DataCurso : public ICollectible{
    private:
        std::string NombreCurso;
        std::string DescripcionCurso;
        TipoDificultad Dificultad;
        bool Habilitado;
    public:
        DataCurso();
        ~DataCurso();
        DataCurso(std::string NombreCurso);
        DataCurso(std::string NombreCurso, std::string DescripcionCurso, TipoDificultad Dificultad, bool Habilitado);
        std::string getNombreCurso();
        std::string getDescripcionCurso();
        TipoDificultad getDificultad();
        bool getHabilitado();       


};

class DataCursoHab: public ICollectible{

    private:
        std::string NombreCurso;
        std::string DescripcionCurso;
        TipoDificultad Dificultad;
        bool Habilitado;
        IDictionary * Lecciones;
        std::string idiomacurso;
        std::string profesorcurso;

        //IDictionary * Registros;

    public:
        DataCursoHab();
        DataCursoHab(std::string NombreCurso, std::string DescripcionCurso, TipoDificultad Dificultad, bool habilitado, std::string idiomacurso , std::string profesorcurso,  IDictionary* Lecciones);
        std::string getNombreCurso();
        std::string getDescripcionCurso();
        TipoDificultad getDificultad();
        std::string getIdiomaCurso();
        std::string getProfesorCurso();
        bool getHabilitado();
        IDictionary * getLecciones();
        //IDictionary * getRegistros();

};

class DataCursoHabMini: public ICollectible{

    private:
        std::string NombreCurso;
        std::string DescripcionCurso;
        bool Habilitado;

    public:
        DataCursoHabMini(std::string NombreCurso, std::string DescripcionCurso);
        DataCursoHabMini(std::string NombreCurso);
        std::string getNombreCurso();
        std::string getDescripcionCurso();
        bool getHabilitado();
};

class DataEstadisticaCurso: public ICollectible{
private:
    std::string nombreCurso;
    double promedioAvance;
    std::string descripcionCurso;
    TipoDificultad dificultadCurso;

public:
    DataEstadisticaCurso(std::string nombreCurso, double promedioAvance, std::string descripcionCurso, TipoDificultad dificultadCurso);
    
    std::string getNombreCurso();
    double getPromedioAvance();
    std::string getDescripcion();
    TipoDificultad getDificultadCurso();
    
};


class InscripcionInfo: public ICollectible{

    private:
        std::string estudianteNombre;
        Date fechaIns;
    public:
        InscripcionInfo(std::string nombre, Date fecha);
        std::string getEstudianteNombre();
        Date getFechaIns();



};

#endif