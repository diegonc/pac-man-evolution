#ifndef __MAPAIMPMATRIZ_H__
#define __MAPAIMPMATRIZ_H__

#include "Mapa.h"
#include "Jugador.h"
#include <list>

/** @brief Implementa una interfaz de mapa
 *
 */

class MapaImpMatriz : public Mapa
{
	//Como vamos a mapear el grafo que tiene cantidades enteras de lados y 
	//hacer la conversion entre (x,y) a lugar en el grafo, lo pongo asi,
	//de ultima se cambia el typedef
	typedef unsigned int Tipo_Dimensiones; 
	
	typedef double Tipo_Coordenada;
	
	typedef S_ptr<Comestible> Tipo_Comestible;
	
	private:
		
		Tipo_Dimensiones ancho;
		Tipo_Dimensiones alto;
		
		struct Casillero {
			Tipo_Comestible comestible;
		
		
	public:
		MapaImpMatriz(Tipo_Dimensiones ancho, Tipo_Dimensiones alto);

		~MapaImpMatriz();
	
		void mover( S_ptr<Jugador> jugador, Direccion dir );

		S_ptr<Comestible> get_comestible(Tipo_Coordenada pos_x, Tipo_Coordenada pos_y);	
	
		Tipo_Dimensiones get_ancho();
	
		Tipo_Dimensiones get_alto();
};

#endif /* __MAPAIMPMATRIZ_H__ */
