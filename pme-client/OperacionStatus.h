#ifndef OPERACIONSTATUS_H_INCLUDED
#define OPERACIONSTATUS_H_INCLUDED

#include <list>
#include <server/Operacion.h>

class OperacionStatus:public Operacion{
    public:

    struct PosicionJugador{
	bool estaVivo;
	bool esPacman;
        unsigned int ID;
        unsigned int Arista;
        unsigned int Posic;
        unsigned int direcc;
        bool marcado;
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
		OperacionStatus(){}
			
		~OperacionStatus(){}
		
		unsigned int get_puntuacion();
	
		void set_puntuacion(unsigned int punt);
	
		std::list<PosicionJugador>* get_jugadores();
	
		std::list<PosicionElemento>* get_elementos();
	
		virtual void ejecutar(ModeloCommon &modelo);

    private:

    	void ModificarPosicionJugador( Jugador * Jug,PosicionJugador& PosJ,int AnchoMapa,int AltoMapa);

};


#endif // OPERACIONSTATUS_H_INCLUDED
