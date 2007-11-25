#ifndef __MAPAIMPMATRIZ_H__
#define __MAPAIMPMATRIZ_H__

#include "Mapa.h"
#include "Jugador.h"
#include "Posicion.h"
#include "ComparadorPosicion.h"

#include <set>

#define TAM_CASILLERO	1;

/** @brief Implementa una interfaz de mapa
 *
 */

//Como vamos a mapear el grafo que tiene cantidades enteras de lados y 
//hacer la conversion entre (x,y) a lugar en el grafo, lo pongo asi,
//de ultima se cambia el typedef
typedef unsigned int Tipo_Dimensiones; 

class MapaImpMatriz : public Mapa{
		
	private:
		friend class ComparadorPosicion;	
	
	
		Tipo_Dimensiones ancho;
		Tipo_Dimensiones alto;
		
		struct Elemento{
			Posicion posicion;
			S_ptr<Estructural> estructural;	
						
		}
		
		std::set<Elemento,ComparadorPosicion> estructurales;	
		
	public:
		
		MapaImpMatriz(const Tipo_Dimensiones ancho, const Tipo_Dimensiones alto);

		~MapaImpMatriz();
	
		void mover( Jugador * jugador, Direccion &dir );
		
		void agregar_estructural(S_ptr<Estructural> e, Posicion &p);
		
		S_ptr<Estructural> get_estructural(Posicion &p);
	
		Tipo_Dimensiones get_ancho();
	
		Tipo_Dimensiones get_alto();
};

#endif /* __MAPAIMPMATRIZ_H__ */
