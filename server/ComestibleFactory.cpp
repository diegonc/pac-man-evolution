#include "ComestibleFactory.h"
#include "PowerUp.h"
#include "Frutita.h"
#include "Quesito.h"

ComestibleFactory::ComestibleFactory(ComestibleFactory &c){}

ComestibleFactory::ComestibleFactory(){}
	
ComestibleFactory::~ComestibleFactory(){}

Comestible * ComestibleFactory::construir(Tipo_Comestible &tipo){
	
	switch(tipo){
		case power_up:	return new PowerUp();
						break;
		case quesito:	return new Quesito();
						break;
		case frutita:	return new Frutita();
						break;
		default: 		//TODO tirar excepcion
						return 0;
						break;
	}

}
