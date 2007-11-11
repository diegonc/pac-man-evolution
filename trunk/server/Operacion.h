#ifndef __OPERACION_H__
#define __OPERACION_H__

/** @brief Interfaz de operaciones sobre el modelo.
 */
class Operacion
{
	public:
		/** @brief Ejecuta la operacion.
		 */
		virtual void ejecutar() = 0;
	
		virtual ~Operacion(){}
};

#endif /* __OPERACION_H__ */
