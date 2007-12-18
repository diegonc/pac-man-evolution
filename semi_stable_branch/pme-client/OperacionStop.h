#ifndef __OPERACION_STOP_H__
#define __OPERACION_STOP_H__

#include "../common/Operacion.h"
#include "ModeloServidor.h"

class OperacionStop : public Operacion
	{
		private:
			
			char Razon;
			int Puntuacion;
		public:
			OperacionStop( char Razon, int Puntuacion);

			void ejecutar(ModeloCommon &modelo);
			
	};
	
#endif /*__OPERACION_STOP_H__*/
