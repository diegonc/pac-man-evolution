#include "ComestibleFactory.h"

ComestibleFactory::ComestibleFactory(&c){}

ComestibleFactory::ComestibleFactory(){}
	
ComestibleFactory::~ComestibleFactory(){}

Comestible * ComestibleFactory::construir(Tipo_Comestible &tipo){
	switch(tipo){
		case PowerUp:	return new PowerUp();
						break;
		case Quesito:	return new Quesito();
						break;
		case Frutita:	return new Frutita();
						break;
		case default: 	//TODO tirar excepcion
						return 0;
						break;
	}

}
