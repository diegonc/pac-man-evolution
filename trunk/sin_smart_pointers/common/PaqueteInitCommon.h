#ifndef __PAQUETEINITCOMMON_H__
#define __PAQUETEINITCOMMON_H__

#include "Paquete.h"
#include "MapaBajoNivel.h"
#include "../common/smart_pointer.h"

class PaqueteInitCommon : public Paquete
{
	protected:
		/** @brief Determina si el cliente que recibe el paquete es el pacman o no.
		 */
		bool esPacman;

		/** @brief MapaBajoNivel en el que se desarrolla el juego.
		 */
		MapaBajoNivel* mapa;

		void agregar_arista( int x, int y, bool norte );
		
		void reemplazar_estructural( EstructuralUnitario * e );
		void remplazar_comestible(EstructuralUnitario * e ,Comestible::Enum_Comestible tipoCom );

		bool escribir_estructural( EstructuralUnitario * e, OutputBitStream& bs );
		bool escribir_comestible( Comestible * c, OutputBitStream& bs );

	public:
		/** Crea un paquete apto para deserializar. */
		PaqueteInitCommon();

		/** Crea un paquete apto para serializar. */
		PaqueteInitCommon( bool pacman, MapaBajoNivel* m );

		void serialize( OutputBitStream& bs );

		void deserialize( InputBitStream& bs );
	
		virtual Operacion * get_operacion()=0;
};

#endif /* _PAQUETEINITCOMMON_H__ */
