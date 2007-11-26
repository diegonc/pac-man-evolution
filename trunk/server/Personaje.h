#ifndef __PERSONAJE_H__
#define __PERSONAJE_H__


class Personaje
{
	private:
		
		double Velocidad;
	
	public:
		
		virtual void comer(Jugador * jugador, Comestible * comestible) = 0;
	
		virtual void colision(Personaje * personaje) = 0;
	
		
	
};

#endif /* __PERSONAJE_H__ */
