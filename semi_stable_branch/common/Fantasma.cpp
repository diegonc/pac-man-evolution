#include "Fantasma.h"
#include "PacMan.h"
#include <math.h>

const double Fantasma::VELOCIDAD_FANTASMA_INICIAL 	= 5;
const double Fantasma::VELOCIDAD_FANTASMA_PW		= 3;
const double Fantasma::RADIO_FANTASMA				= 0.5;

Fantasma::Fantasma(Jugador *jugador):Personaje(jugador, RADIO_FANTASMA){
	//this->velocidad = 	
}
	

bool Fantasma::comer(Comestible& comestible){
	/*POR EL MOMENTO NO COME NADA*/
	return false;
}
	
void Fantasma::colision(Jugador * jugador){
	//verifica que el personaje con el que colisiono sea uno al cual le afecte,
	//en este caso, pacman
	if(this->esta_vivo() && jugador->get_personaje()->esta_vivo() ){
		try{
			//si el jugador no es si mismo, ya que no tiene sentido
			if(jugador->get_id() != get_jugador()->get_id() ){
				//trata de castear a pacman, si da error, pasa al catch
				PacMan pacman = dynamic_cast< PacMan& >(*jugador->get_personaje());
				Tipo_Coordenada distancia;
				
				//calcula la distancia entre los dos personajes calculando el modulo
				// dist = ( ( x0 - x1 )² + ( y0 - y1)² )^ ½
				distancia = pow( get_jugador()->get_posicion().get_x() - 	
							 jugador->get_posicion().get_x() , 2);
			
				distancia += pow( get_jugador()->get_posicion().get_y() - 	
							  jugador->get_posicion().get_y() , 2);
			
				distancia = sqrt(distancia);
				
				//si la distancia es menor o igual que la suma de los radios, 
				//quiere decir que chocaron
				if(distancia  <= ( this->get_radio() + pacman.get_radio() ) ){
					if( !pacman.tiene_power_up() ){
						//obtengo los personajes					
						Personaje * p_this = this->get_jugador()->get_personaje();
						Personaje * p_jug = jugador->get_personaje();
						//cambio los personajes
						jugador->set_personaje(p_this);
						this->get_jugador()->set_personaje(p_jug);
						//cambio los jugadores
						p_jug->set_jugador(this->get_jugador());
						p_this->set_jugador(jugador);
						//mato al fantasma
						p_this->matar();
						
					}
					else{
						if(jugador->get_personaje()->esta_vivo())
							this->matar();
					}
				}
			}
		}
		catch(std::bad_cast &e){/*No hago nada ya que no pasa anda cuando choca
									con fantasmas*/}
	}
	
}

Personaje::Enum_Personaje Fantasma::get_tipo(){
	Personaje::Enum_Personaje tipo = fantasma;
	
	return tipo;
}
double Fantasma::get_velocidad(){
	//TODO intercambio de velocidades cuando esta muerto y vivo, etcs
	return VELOCIDAD_FANTASMA_INICIAL;
}
