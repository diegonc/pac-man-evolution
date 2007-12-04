#include "PowerUp.h"
#include <typeinfo>
#include "PacMan.h"
#include <stdexcept>

PowerUp::PowerUp(Posicion &p):Comestible(PUNTOS_POWER_UP, p){}
		
PowerUp::~PowerUp(){}
		
void PowerUp::afectar_personaje(Personaje& personaje){
	try{
		//trato de castear al pacman ya que es al unico que lo afecta
		PacMan *pacman = dynamic_cast<PacMan*>(&personaje);
		//le pongo al pacman el power_up activado
		pacman->set_power_up(true);
	}
	catch(std::bad_cast &e){/*No hago nada*/}
	
		
}
Comestible::Enum_Comestible PowerUp::get_tipo(){
	return Comestible::power_up;
}
