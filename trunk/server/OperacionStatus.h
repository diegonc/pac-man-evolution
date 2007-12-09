#ifndef OPERACIONSTATUS_H_INCLUDED
#define OPERACIONSTATUS_H_INCLUDED

#include <iostream>
#include <list>
#include "Operacion.h"

class OperacionStatus:public Operacion{
    public:

    struct PosicionJugador{
        unsigned int ID;
        unsigned int Arista;
        unsigned int Posic;
        unsigned int direcc;
    };

    struct PosicionElemento{
        char Tipo;
        unsigned int Orient;
        unsigned int Estado;
        unsigned int Posic;
    };
    //valores a aplicar

    private:
    unsigned int Puntuacion;

    std::list<PosicionJugador> Jugadores;
    std::list<PosicionElemento> Elementos;

    public:

    unsigned int get_puntuacion(){
        return Puntuacion;
    }

    void set_puntuacion(unsigned int punt){
        Puntuacion=punt;
    }

    std::list<PosicionJugador>* get_jugadores(){
        return &Jugadores;
    }

    std::list<PosicionElemento>* get_elementos(){
        return &Elementos;
    }

    virtual void ejecutar(ModeloServidor &modelo){}

};


#endif // OPERACIONSTATUS_H_INCLUDED
