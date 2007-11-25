#ifndef __MAPAIMPMATRIZ_H__
#define __MAPAIMPMATRIZ_H__

#include "Mapa.h"
#include "Jugador.h"
#include "Posicion.h"
#include "Casillero.h"
#include "ComestibleFactory.h"

#define TAM_CASILLERO	1;

/** @brief Implementa una interfaz de mapa
 *
 */

//Como vamos a mapear el grafo que tiene cantidades enteras de lados y 
//hacer la conversion entre (x,y) a lugar en el grafo, lo pongo asi,
//de ultima se cambia el typedef
typedef unsigned int Tipo_Dimensiones; 

class MapaImpMatriz : public Mapa{
		
	typedef S_ptr<Comestible> Tipo_Comestible;
	
	public:
		enum Tipo {
        	Nada, Pasillo, Salida_PacMan, CasaFantasma
    	};
	
	private:
		
		Tipo_Dimensiones ancho;
		Tipo_Dimensiones alto;
		
		S_ptr<Casillero> ** matriz;		
		
		//Casillero& get_comestible(Posicion &posicion);	
		
	public:
		
		MapaImpMatriz(const Tipo_Dimensiones ancho, const Tipo_Dimensiones alto);

		~MapaImpMatriz();
	
		void mover( Jugador * jugador, Direccion &dir );
	
		void agregar_casillero( S_ptr<Casillero> casillero_nuevo, Posicion posicion, 
	                            bool tiene_vecino_izq, bool tiene_vecino_arr );
	
		
			
		Tipo_Dimensiones get_ancho();
	
		Tipo_Dimensiones get_alto();
};

#endif /* __MAPAIMPMATRIZ_H__ */
