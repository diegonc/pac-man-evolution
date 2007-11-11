#ifndef __CODEC_H__
#define __CODEC_H__

#include "Operacion.h"
#include "Paquete.h"
#include "../common/smart_pointer.h"

/** @brief Codificador y decodificador de operaciones.
 *
 *  Realiza la traduccion entre paquetes provenientes de la red y operaciones
 *  aplicables al modelo.
 */
class Codec
{
	private:
		Codec();
		Codec(Codec& c);
		static S_ptr<Codec> instancia;
		
	public:
		static S_ptr<Codec> get_instancia();
		~Codec();
		
		/** @brief Transforma paquetes en operaciones.
		 *
		 *  @param pkt Paquete a traducir.
		 *  @return Retorna una nueva operacion.
		 */
		Operacion* procesar( Paquete* pkt );

		/** @brief Transforma operaciones en paquetes.
		 *
		 *  @param op Operacion a traducir.
		 *  @return Retorna un nuevo paquete.
		 */
		Paquete* procesar( Operacion* op );
};

#endif /* __CODEC_H__ */
