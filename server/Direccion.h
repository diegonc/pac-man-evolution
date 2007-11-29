#ifndef __DIRECCION_H__
#define __DIRECCION_H__

/** @brief Define las direccion permitidas para un jugador.
 *  
 *  Las direcciones Norte, Sur, Este, Oeste se definen como atributos de clase.
 *  El objeto es inmutable.
 */
 
 #include <iostream>
 
class Direccion
{
	private:
		Direccion( int i );

	public:
		static Direccion Norte;
		static Direccion Sur;
		static Direccion Este;
		static Direccion Oeste;
	
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
		Direccion combinar( int i );
	
	
		friend std::ostream& operator <<( std::ostream& os, const Direccion &dir) 
     	{ 
         	switch(dir.dir){
				case 0 : os << "Norte";
						 break;	
				case 1 : os << "Sur";
						break;
				case 2 : os << "Este";
						break;
				case 3 : os << "Oeste";
						 break;

				
			}
         	// return ostream object 
         	return os; 
     	}
		//Direccion( Direccion& d );
		
};

#endif /* __DIRECCION_H__ */
