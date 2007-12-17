#ifndef _OPERACION_INIT_COMMON_H
#define _OPERACION_INIT_COMMON_H

#include <server/Operacion.h>

class OperacionInit : public Operacion
	{
		private:
			S_ptr<MapaBajoNivel> m;
			bool esPac;
		public:
			OperacionInit( S_ptr<MapaBajoNivel> m, bool esPac );

			void ejecutar(ModeloCommon &modelo);
	};
#endif /*_OPERACION_INIT_COMMON_H*/
