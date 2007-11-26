#ifndef __PACMAN_H__
#define __PACMAN_H__

class PacMan : public Personaje{
	private:
		bool tiene_power_up;
	
	public:
		void comer(Jugador * jugador, Comestible * comestible);
	
		void colision(Personaje * personaje);
}

#endif /*__PACMAN_H__*/
