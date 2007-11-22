#ifndef __PAQUETE_H__
#define __PAQUETE_H__

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
	public:
		virtual ~Paquete();

		char get_tipo();

		//algo similar a esto, que pase a bits
	
		/*Tipo*/void serialize();
};

#endif /* __PAQUETE_H__ */
