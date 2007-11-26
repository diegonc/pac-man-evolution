#ifndef __PAQUETE_H__
#define __PAQUETE_H__

#include "BitStream.h"

class Paquete
{
	private:
		Paquete();
		Paquete(Paquete &p);

		/** @brief Tipo de paquete.
		 *
		 *  Valor numerico que identifica de que tipo es el paquete.
		 *
		 *  La idea seria que se lo pueda utilizar para crear el
		 *  tipo de paquete correspondiente.
		 *  Por ejemplo, tenindo un arreglo de funciones:
		 *        Paquete* p = a[ tipo ]();
		 */
		/*TODO: enum? solo algun typedef y despues PaqueteEspecifico::ID?
		 */char tipo;

	protected:
		/** @brief Constructor para subtipos.
		 *
		 *  Constructor protegido para que subtipos puedan establecer
		 *  el valor correcto del tipo.
		 */ 
		Paquete( char tipo );

	public:
		/** @brief Metodo fabrica de paquetes.
		 *
		 *  Crea nuevos paquetes del tipo requerido sin inicializar,
		 *  aptos para ser deserializados.
		 *
		 *  @param tipo Identificador numerico del tipo de paquete.
		 *  @return Paquete creado.
		 */
		static Paquete* crear( int tipo );

		virtual ~Paquete();

		char get_tipo();

		//algo similar a esto, que pase a bits
	
		/*Tipo*/void serialize();

		/** @brief Carga el estado del objeto desde un BitStream.
		 *
		 *  @param bs Fuente de datos.
		 */
		void deserialize( BitStream& bs ) = 0;
};

#endif /* __PAQUETE_H__ */
