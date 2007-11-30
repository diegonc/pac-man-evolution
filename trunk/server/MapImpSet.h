#ifndef __MAPAIMPMATRIZ_H__
#define __MAPAIMPMATRIZ_H__

#include "MapaBajoNivel.h"
#include "Jugador.h"
#include "Posicion.h"
#include "ComparadorPosicion.h"
#include "Comestible.h"
#include <set>

/** @brief Implementa una interfaz de mapa
 *
 */

typedef unsigned int Tipo_Dimensiones;
typedef S_ptr<EstructuralUnitario> Tipo_Estructural;

class MapaImpSet : public MapaBajoNivel{

	private:

		Tipo_Dimensiones ancho;
		Tipo_Dimensiones alto;

		Tipo_Estructural estructural;


		//bool tocando(Tipo_Coordenada dim_actual, Tipo_Coordenada dim_final, S_ptr<EstructuralUnitario> vecino, Jugador& jugador);

		bool tocando(Jugador &jugador, Posicion &pnueva);
		//void set_dim(Posicion& p, Tipo_Coordenada& dim_actual, Tipo_Coordenada& dim_final, Direccion& dir);

	public:
		class CompSptrEstructuralPosicion{
			public:
				bool operator()(const Tipo_Estructural &e1, const Tipo_Estructural &e2){
					Tipo_Estructural v1 = e1;
					Tipo_Estructural v2 = e2;

					Posicion pos1 = v1->get_posicion();
					Posicion pos2 = v2->get_posicion();
	
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
		std::set<Tipo_Estructural,CompSptrEstructuralPosicion> estructurales;
		std::list<S_ptr<Comestible> > comestibles;

		void quitar_comestible(S_ptr<Comestible> comestible);

	public:

		MapaImpSet(const Tipo_Dimensiones ancho, const Tipo_Dimensiones alto);

		~MapaImpSet();

		void mover( Jugador& jugador, Tipo_Coordenada distancia );

		void agregar_estructural(S_ptr<EstructuralUnitario> e);

		S_ptr<EstructuralUnitario> get_estructural(Posicion &p);

		std::list<S_ptr<EstructuralUnitario> > get_estructurales();

		std::list<S_ptr<Comestible> > get_comestibles();
	
		Tipo_Dimensiones get_ancho();

		Tipo_Dimensiones get_alto();
};

#endif /* __MAPAIMPMATRIZ_H__ */
