#ifndef __MAPAIMPMATRIZ_H__
#define __MAPAIMPMATRIZ_H__

#include "Mapa.h"
#include "Jugador.h"
#include "Posicion.h"
#include "ComparadorPosicion.h"

#include <set>

/** @brief Implementa una interfaz de mapa
 *
 */
 
typedef unsigned int Tipo_Dimensiones;
class MapaImpSet : public Mapa{
		
	private:
		Tipo_Dimensiones ancho;
		Tipo_Dimensiones alto;
	
		class Elemento{
			public:
				Posicion posicion;
				S_ptr<Estructural> estructural;	
		};
	public:
		class ComparadorElementoPosicion{
			public:
				bool operator()(const Elemento &e1, const Elemento &e2){
					Posicion pos1 = (e1.posicion);
					Posicion pos2 = (e2.posicion);

					if( (int)pos1.get_x() < (int)pos2.get_x() ) 
						return true;
					else
						if((int)pos1.get_y() < (int)pos2.get_y())
							return true;
						else
							return false;
					}
		};
	private:
		std::set<Elemento,ComparadorElementoPosicion> estructurales;	
		
	public:
		
		MapaImpSet(const Tipo_Dimensiones ancho, const Tipo_Dimensiones alto);

		~MapaImpSet();
	
		void mover( Jugador& jugador, Direccion &dir, Tipo_Coordenada distancia );
		
		void agregar_estructural(S_ptr<Estructural> e, Posicion &p);
		
		S_ptr<Estructural> get_estructural(Posicion &p);
	
		Tipo_Dimensiones get_ancho();
	
		Tipo_Dimensiones get_alto();
};

#endif /* __MAPAIMPMATRIZ_H__ */
