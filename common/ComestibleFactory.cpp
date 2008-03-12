#include "ComestibleFactory.h"

#include "../common/PowerUp.h"
#include "../common/Frutita.h"
#include "../common/Quesito.h"


ComestibleFactory::ComestibleFactory(ComestibleFactory &c){}

ComestibleFactory::ComestibleFactory(){}
	
ComestibleFactory::~ComestibleFactory(){}

Comestible * ComestibleFactory::construir(Comestible::Enum_Comestible tipo, Posicion &p){
	
	//se implemento mediante un switch
	switch(tipo){
		case _POWER_UP:	
				return new PowerUp(p);
				break;
		case _QUESITO:	
				return new Quesito(p);
				break;
		case _FRUTITA:
				return new Frutita(p);
				break;
		default://TODO tirar excepcion?
				return 0;
	}

}
