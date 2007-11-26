#include "PowerUp.h"
#include <typeinfo>
#include "PacMan.h"
#include <stdexcept>

PowerUp::PowerUp():Comestible(PUNTOS_POWER_UP){}
		
PowerUp::~PowerUp(){}
		
void PowerUp::afectar_personaje(Personaje& personaje){
	try{
		PacMan pacman = dynamic_cast< PacMan& >(personaje);
		pacman.set_power_up(true);
	}
	catch(std::bad_cast &e){/*No hago nada*/}
	
		
}
