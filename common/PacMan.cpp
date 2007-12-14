#include "PacMan.h"
#include <math.h>

#define VELOCIDAD_PACMAN_NORMAL		3	/*3 u/s */
#define VELOCIDAD_PACMAN_PW		5
#define RADIO_PACMAN			0.5

PacMan::PacMan(Jugador *jugador):Personaje(jugador,RADIO_PACMAN){
	this->set_power_up(false);
}

bool PacMan::comer(Comestible& comestible){
	//incremento los puntos del jugador dependiendo del comestible
	(this->get_jugador())->incrementar_puntos(comestible.get_puntos());
	//afecto a este personaje
	comestible.afectar_personaje(*this);
	//devuelvo true ya que lo comio
	return true;	
}
void PacMan::colision(Jugador * jugador){
	if(this->esta_vivo() && jugador->get_personaje()->esta_vivo() ){
		//si no es el mismo jugador
		if(jugador->get_id() != get_jugador()->get_id() ){
			Tipo_Coordenada distancia;
			//calcula la distancia entre los dos personajes calculando el modulo
			// dist = ( ( x0 - x1 )² + ( y0 - y1)² )^ ½
			distancia = pow( get_jugador()->get_posicion().get_x() - 	
							 jugador->get_posicion().get_x() , 2);
			
			distancia += pow( get_jugador()->get_posicion().get_y() - 	
							  jugador->get_posicion().get_y() , 2);
			
			distancia = sqrt(distancia);
			//si la distancia es menor o igual que la suma de los radios, 
			//quiere decir que choca
			if(distancia  <= (this->get_radio() + jugador->get_personaje()->get_radio() ) ){
				if( this->tiene_power_up() ){
					//if(jugador->get_personaje()->esta_vivo()) <<---CREO QUE NO HACE FALTA
						jugador->get_personaje()->matar();
				}
				else{
					//obtengo los personajes					
					S_ptr<Personaje> p_this = this->get_jugador()->get_personaje();
					S_ptr<Personaje> p_jug = jugador->get_personaje();
					//cambio los personajes
					jugador->set_personaje(p_this);
					this->get_jugador()->set_personaje(p_jug);
					//cambio los jugadores
					p_jug->set_jugador(this->get_jugador());
					p_this->set_jugador(jugador);
					//mato al personaje que no es pacman
					p_jug->matar();
					
				}
			}
		}		
	}
}
void PacMan::set_power_up(bool activado){
	this->power_up_activado = activado;
	if(activado)
		this->velocidad = VELOCIDAD_PACMAN_PW;
	else
		this->velocidad = VELOCIDAD_PACMAN_NORMAL;
}
bool PacMan::tiene_power_up(){
	return this->power_up_activado;
}
Personaje::Enum_Personaje PacMan::get_tipo(){
	return pacman;
}
double PacMan::get_velocidad(){
	return 	this->velocidad;
}
