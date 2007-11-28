#include "ComestibleFactory.h"
#include "PowerUp.h"
#include "Frutita.h"
#include "Quesito.h"


ComestibleFactory::ComestibleFactory(ComestibleFactory &c){}

ComestibleFactory::ComestibleFactory(){}
	
ComestibleFactory::~ComestibleFactory(){}

Comestible * ComestibleFactory::construir(Comestible::Enum_Comestible tipo){
	
	switch(tipo){
		case 0:	return new PowerUp();
				break;
		case 1:	return new Quesito();
				break;
		case 2:	return new Frutita();
				break;
		default://TODO tirar excepcion?
				return 0;
	}

}
