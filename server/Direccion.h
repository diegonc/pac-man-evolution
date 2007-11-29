#ifndef __DIRECCION_H__
#define __DIRECCION_H__


#define NORTE	0
#define ESTE	1
#define SUR		2
#define OESTE	3

/** @brief Define las direccion permitidas para un jugador.
 *  
 *  Las direcciones Norte, Sur, Este, Oeste se definen como atributos de clase.
 *  El objeto es inmutable.
 */
 
 #include <iostream>
 
class Direccion
{
	public:
		Direccion( int i );
	
		static const int Norte;
		static const int Sur;
		static const int Este;
		static const int Oeste;
	
	private:
		
		int dir;

	public:
		/** @brief Cambia de direccion i veces.
		 *
		 *  Realiza un numero |i| de giros en sentido horario si i>0 o
		 *  antihorario si i<0, a partir de la direccion actual.
		 *  Los giros son unicamente de 90�, resultando en direcciones finales
		 *  contenidas en el conjunto { Norte, Sur, Este, Oeste }.
		 *
		 *  @param i Numero de giros.
		 *  @return Direccion resultante.
		 */
		void combinar( int i );
	
		friend std::ostream& operator <<( std::ostream& os, const Direccion &dir) 
     	{ 
         	switch(dir.dir){
				case NORTE : os << "Norte";
						 break;	
				case SUR : os << "Sur";
						break;
				case ESTE : os << "Este";
						break;
				case OESTE : os << "Oeste";
						 break;

				
			}
         	// return ostream object 
         	return os; 
     	}
		
		const int get_dir();
		
		//Direccion( Direccion& d );
		
};

#endif /* __DIRECCION_H__ */