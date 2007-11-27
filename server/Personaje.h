#ifndef __PERSONAJE_H__
#define __PERSONAJE_H__


class Jugador;
class Comestible;

class Personaje{
	private:
		Jugador * jugador;
		double radio;
		double Velocidad;
		bool vivo;
	
	protected:	
		Personaje(Jugador * jugador, double radio);
	
		Jugador& get_jugador();
	
	public:
		void matar();

		void revivir();
	
		bool esta_vivo();
		
		virtual ~Personaje();	
	
		virtual void comer(Comestible& comestible) = 0;
	
		virtual void colision(Jugador& jugador) = 0;
	
		double get_radio();
	
};

#endif /* __PERSONAJE_H__ */
