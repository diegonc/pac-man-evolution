#ifndef __PERSONAJE_H__
#define __PERSONAJE_H__


class Jugador;
class Comestible;

class Personaje{
	private:
		
		double Velocidad;
	
	protected:	
		Personaje(){}
	
	public:
	
		virtual ~Personaje(){};	
	
		virtual void comer(Jugador& jugador, Comestible& comestible) = 0;
	
		virtual void colision(Jugador& jugador) = 0;
	
		
	
};

#endif /* __PERSONAJE_H__ */
