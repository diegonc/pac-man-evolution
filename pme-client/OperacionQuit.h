#ifndef __OPERACION_QUIT_H__
#define __OPERACION_QUIT_H__

#include <server/Operacion.h>
#include "ModeloServidor.h"

class OperacionQuit : public Operacion
	{
		private:


		public:
			OperacionQuit();

			void ejecutar(ModeloCommon &modelo);
			
	};
	
#endif /*__OPERACION_QUIT_H__*/
