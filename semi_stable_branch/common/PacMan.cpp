#include "PacMan.h"
#include <common/thread.h>
#include <math.h>
#include <cassert>

const double PacMan::VELOCIDAD_PACMAN_NORMAL 	= 3;
const double PacMan::VELOCIDAD_PACMAN_PW 		= 5;
const double PacMan::RADIO_PACMAN		 		= 0.5;

class PacMan::RemovedorPowerUp : public Thread
{
	PacMan& pacman;

	void run( );

	void cancel( );

	public:
		RemovedorPowerUp( PacMan& p );

		~RemovedorPowerUp();
};

void PacMan::RemovedorPowerUp::run()
{
	/* TODO: mover a Thread ?*/
	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL );

	sleep( 5 );
	pacman.set_power_up( false );
}

void PacMan::RemovedorPowerUp::cancel()
{
	if( this->corriendo() ) {
		/* TODO: mover a Thread */
		pthread_cancel( this->get_hilo() );
	}
	this->join();
}

PacMan::RemovedorPowerUp::RemovedorPowerUp( PacMan& p ) : pacman( p ) { }

PacMan::RemovedorPowerUp::~RemovedorPowerUp( )
{
	this->cancel();
}

PacMan::PacMan(Jugador *jugador):Personaje(jugador,RADIO_PACMAN){
	this->set_power_up(false);
	this->velocidad = VELOCIDAD_PACMAN_NORMAL;
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
					Personaje * p_this = this->get_jugador()->get_personaje();
					Personaje * p_jug = jugador->get_personaje();
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
	if(activado) {
		this->velocidad = VELOCIDAD_PACMAN_PW;
		this->removedor = new RemovedorPowerUp( *this );
		this->removedor->start();
		assert( activado == true );
	} else
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
