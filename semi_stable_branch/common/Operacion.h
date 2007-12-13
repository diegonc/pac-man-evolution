#ifndef __OPERACION_H__
#define __OPERACION_H__

   #ifndef PROGRAMA_CLIENTE
      #include "../server/ModeloServidor.h"
   #else
      #include "../client/ModeloServidor.h"
   #endif
/** @brief Interfaz de operaciones sobre el modelo.
 */
class Operacion
{
	public:
		/** @brief Ejecuta la operacion.
		 */
		virtual void ejecutar(ModeloServidor &modelo) = 0;
			
		virtual ~Operacion(){}
};

#endif /* __OPERACION_H__ */
