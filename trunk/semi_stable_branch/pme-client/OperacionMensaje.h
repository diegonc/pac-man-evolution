#ifndef __OPERACION_MENSAJE_H__
#define __OPERACION_MENSAJE_H__

#include <server/Operacion.h>
#include "ModeloServidor.h"

class OperacionMensaje : public Operacion
	{
		private:
			std::string Mensaje;

		public:
			OperacionMensaje( std::string Mensaje );

			void ejecutar(ModeloCommon &modelo);
			
	};
	
#endif /*__OPERACION_START_H__*/
