#include "PowerUp.h"
#include <typeinfo>
#include "PacMan.h"
#include <stdexcept>

PowerUp::PowerUp(Posicion &p):Comestible(PUNTOS_POWER_UP, p){}
		
PowerUp::~PowerUp(){}
		
void PowerUp::afectar_personaje(Personaje& personaje){
	std::cout << "El pacman come powerup\n";
	try{
		PacMan *pacman = dynamic_cast<PacMan*>(&personaje);
		pacman->set_power_up(true);
	}
	catch(std::bad_cast &e){/*No hago nada*/}
	
		
}
Comestible::Enum_Comestible PowerUp::get_tipo(){
	return Comestible::power_up;
}
