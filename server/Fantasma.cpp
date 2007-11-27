#include "Fantasma.h"
#include "PacMan.h"
#include <math.h>

#define RADIO_FANTASMA		0.5


Fantasma::Fantasma(Jugador *jugador):Personaje(jugador, RADIO_FANTASMA){}
	

void Fantasma::comer(Comestible& comestible){
	/*POR EL MOMENTO NO COME NADA*/
}
	
void Fantasma::colision(Jugador& jugador){
	try{
		PacMan pacman = dynamic_cast< PacMan& >(*jugador.get_personaje());
		
		Tipo_Coordenada distancia;
	
		distancia = pow( get_jugador().get_posicion().get_x() - 	
					 jugador.get_posicion().get_x() , 2);
	
		distancia += pow( get_jugador().get_posicion().get_y() - 	
					  jugador.get_posicion().get_y() , 2);
	
		distancia = sqrt(distancia);
	
		if(distancia  <= ( this->get_radio() + pacman.get_radio() ) ){
			if(pacman.tiene_power_up() ){
				std::cout << "Muere el pacman!!\n";
				pacman.matar();
			}
			else{
				std::cout << "Muere el fantasma!!\n";
				this->matar();			
			}
		}
	}
	catch(std::bad_cast &e){/*No hago nada ya que no pasa anda cuando choca
							con fantasmas*/}
}
