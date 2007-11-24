#ifndef __MAPAIMPMATRIZ_H__
#define __MAPAIMPMATRIZ_H__

#include "Mapa.h"
#include "Jugador.h"
#include "Posicion.h"

#define TAM_CASILLERO	1;

/** @brief Implementa una interfaz de mapa
 *
 */

class MapaImpMatriz : public Mapa
{
	//Como vamos a mapear el grafo que tiene cantidades enteras de lados y 
	//hacer la conversion entre (x,y) a lugar en el grafo, lo pongo asi,
	//de ultima se cambia el typedef
	typedef unsigned int Tipo_Dimensiones; 
	
	typedef S_ptr<Comestible> Tipo_Comestible;
	
	public:
		enum Tipo {
        	Nada, Pasillo, Salida_PacMan, CasaFantasma
    	};
	
	private:
		
		Tipo_Dimensiones ancho;
		Tipo_Dimensiones alto;
		
		Casillero * matriz;		
		
		Casillero& get_comestible(Posicion &posicion);	
		
	public:
		
		MapaImpMatriz(Tipo_Dimensiones ancho, Tipo_Dimensiones alto);

		~MapaImpMatriz();
	
		void mover( Jugador * jugador, Direccion dir );
	
		virtual void establecer_posicion_inicial(Jugador * jugador);
			
		void agregar_comestible( Tipo_Comestible comestible, Posicion &posicion);
	
		Tipo_Dimensiones get_ancho();
	
		Tipo_Dimensiones get_alto();
};

#endif /* __MAPAIMPMATRIZ_H__ */
