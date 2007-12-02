#ifndef __DIRECCION_H__
#define __DIRECCION_H__


#define _NORTE	0
#define _ESTE	1
#define _SUR		2
#define _OESTE	3

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
	
		Direccion();
	
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
		 *  Los giros son unicamente de 90º, resultando en direcciones finales
		 *  contenidas en el conjunto { Norte, Sur, Este, Oeste }.
		 *
		 *  @param i Numero de giros.
		 *  @return Direccion resultante.
		 */
		void combinar( int i );
	
		friend std::ostream& operator <<( std::ostream& os, const Direccion &dir) 
     	{ 
         	switch(dir.dir){
				case _NORTE : os << "Norte";
						 break;	
				case _SUR : os << "Sur";
						break;
				case _ESTE : os << "Este";
						break;
				case _OESTE : os << "Oeste";
						 break;

				
			}
         	// return ostream object 
         	return os; 
     	}
		
		const int get_dir();
		
		//Direccion( Direccion& d );
		
};

#endif /* __DIRECCION_H__ */
