#include "PaqueteStatus.h"

#include "OperacionStatus.h"

PaqueteStatus::PaqueteStatus(): PaqueteStatusCommon(){

}
PaqueteStatus::~PaqueteStatus(){}

void PaqueteStatus::deserialize( InputBitStream& bs ){
	
	OperacionStatus * oper = new OperacionStatus();
    OperacionStatus::PosicionElemento PosElem;
    OperacionStatus::PosicionJugador PosJugad;
    unsigned int CantidadJugadores;
    unsigned int CantidadElementos;
    CantidadJugadores=bs.read(3);
    unsigned int temp;
    temp=bs.read(32);
    oper->set_puntuacion(temp);
    for(unsigned int NroJug=0;NroJug<CantidadJugadores;++NroJug){
	PosJugad.estaVivo=(bs.read(1))?true:false;
	PosJugad.esPacman=(bs.read(1))?true:false;
        PosJugad.ID=bs.read(14);
        PosJugad.Arista=bs.read(17);
        PosJugad.Posic=bs.read(6);
        PosJugad.direcc=bs.read(1);
        PosJugad.marcado=false;
        oper->get_jugadores()->push_back(PosJugad);
    }

    CantidadElementos=bs.read(8);

    for(unsigned int NroElem=0;NroElem<CantidadElementos;++NroElem){
        PosElem.Tipo=(char)bs.read(4);
        PosElem.Orient=bs.read(2);
        PosElem.Estado=bs.read(2);
        PosElem.Posic=bs.read(16);
        oper->get_elementos()->push_back(PosElem);
    }
	Oper = oper;
	
}
Operacion * PaqueteStatus::get_operacion(){
   return Oper;
}

