#ifndef __OPERACION_H__
#define __OPERACION_H__

class Operacion
{
	public:
		virtual void ejecutar() = 0;
	
		virtual ~Operacion(){}
};

#endif /* __OPERACION_H__ */
