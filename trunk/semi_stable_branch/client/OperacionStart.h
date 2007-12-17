#ifndef __OPERACION_START_H__
#define __OPERACION_START_H__

#include "../common/Operacion.h"

class OperacionStart : public Operacion
	{
		private:
			int id;

		public:
			OperacionStart( int id );

			void ejecutar(ModeloCommon &modelo);
			
	};
	
#endif /*__OPERACION_START_H__*/
