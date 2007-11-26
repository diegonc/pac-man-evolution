#include "PowerUp.cpp"

PowerUp::PowerUp():Comestible(PUNTOS_POWER_UP){}
		
PowerUp::~PowerUp(){}
		
void PowerUp::afectar_personaje(Personaje& personaje){
	personaje->set_power_up(true);
}
