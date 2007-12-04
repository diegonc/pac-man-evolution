#ifndef __PERSONAJE_H__
#define __PERSONAJE_H__

/**
*	@brief	Clase que repesenta al personaje que esta jugando. Hay uno por jugador.
			Su dimension esta representada por una bola.
*/

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
		//definiciones
		static const char pacman;
		static const char fantasma;
		
		typedef const char Enum_Personaje;	
	
		/**
		*	@brief	Metodo que settea como muerto al personaje
		*/
		void matar();
	
		/**
		*	@brief	Metodo que settea como vivo al personaje
		*/
		void revivir();
	
		/**
		*	@brief	Metodo que permite saber el estado del personaje
		*
		*	@return	true si esta vivo, false en caso contrario
		*/
		bool esta_vivo();
		
		/**
		*	@brief 	Destructor de la clase
		*/
		virtual ~Personaje();	
	
		/**
		*	@brief 	Debe implementar las operaciones que se realizan al comer
		*			un comestible y sus efectos sobre el personaje
		*
		*	@param	comestible Comestible que come el personaje
		*
		*	@return true si pudo comer, false caso contrario
		*/
		virtual bool comer(Comestible& comestible) = 0;
	
		/**
		*	@brief 	Debe implementar las operaciones que se realizan al colisionar
		*			dos personajes
		*
		*	@param	jugador Jugador que posee el personaje con el cual choca
		*/
		virtual void colision(Jugador& jugador) = 0;
	
		/**
		*	@brief 	Debe devolver el tipo de personaje que es.
		*
		*	@return tipo de personaje al cual corresponde. El tipo debe ser del
		*			definido arriba
		*/
		virtual Enum_Personaje get_tipo() = 0;
	
		/**
		*	@brief 	Debe devolver la velocidad del personaje
		*
		*	@return la velocidad del personaje
		*/
		virtual double get_velocidad() = 0;
		
		/**
		*	@brief 	Devuelve el radio del personaje.
		*
		*	@return radio del personaje
		*/
		
		double get_radio();
		
		
	
};

#endif /* __PERSONAJE_H__ */
