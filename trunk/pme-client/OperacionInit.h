#ifndef _OPERACION_INIT_COMMON_H
#define _OPERACION_INIT_COMMON_H

#include <server/Operacion.h>

class OperacionInit : public Operacion
	{
		private:
			MapaBajoNivel* m;
			bool esPac;
		public:
			OperacionInit( MapaBajoNivel* m, bool esPac );

			void ejecutar(ModeloCommon &modelo);
	};
#endif /*_OPERACION_INIT_COMMON_H*/
