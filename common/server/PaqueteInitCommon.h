#ifndef __PAQUETEINITCOMMON_H__
#define __PAQUETEINITCOMMON_H__

#include <server/Paquete.h>
#include <server/MapaBajoNivel.h>
#include <common/smart_pointer.h>

class PaqueteInitCommon : public Paquete
{
	protected:
		/** @brief Determina si el cliente que recibe el paquete es el pacman o no.
		 */
		bool esPacman;

		/** @brief MapaBajoNivel en el que se desarrolla el juego.
		 */
		S_ptr<MapaBajoNivel> mapa;

		void agregar_arista( int x, int y, bool norte );

		void reemplazar_estructural( S_ptr<EstructuralUnitario>& e );
		void remplazar_comestible(S_ptr<EstructuralUnitario>& e ,Comestible::Enum_Comestible tipoCom );

		bool escribir_estructural( S_ptr<EstructuralUnitario>& e, OutputBitStream& bs );
		bool escribir_comestible( S_ptr<Comestible>& c, OutputBitStream& bs );

	public:
		/** Crea un paquete apto para deserializar. */
		PaqueteInitCommon();

		/** Crea un paquete apto para serializar. */
		PaqueteInitCommon( bool pacman, S_ptr<MapaBajoNivel> m );

		void serialize( OutputBitStream& bs );

		void deserialize( InputBitStream& bs );
	
		virtual Operacion * get_operacion()=0;
};

#endif /* _PAQUETEINITCOMMON_H__ */
