#ifndef __OUTPUTBITSTREAM_H__
#define __OUTPUTBITSTREAM_H__

/**
*	@brief	Esta clase permite ir acumulando bits. 
*			Alinea al byte.
*/


#define _DEFAULT_SIZE	1 // 8 bits

class OutputBitStream
{
	private:
		unsigned char * buffer;
		unsigned char * _return; //TODO!! CORREGIR
		unsigned int bit_index;
		unsigned int buffer_size;
	
		void shift_left(const unsigned int n_bits);
			
	public:
		/**
		*	@brief	Constructor
		*/
		OutputBitStream();
		
		/**
		*	@brief	Destructor
		*/
		~OutputBitStream();	
	
		/**
		*	@brief 	Reseva n bits para un numero en los lugares mas bajos del
		*			Stream, lo convierte a binario y lo almacena.
		*			Si el numero no entra en el espacio, se guarda solo la
		*			parte mas baja del mismo.
		*			Si no hay espacio suficiente para la cantidad de bits deseados
		*			se puede aumentar o no realizar operacion alguna.
		*
		*	@param	n Lugares reservados para el numero
		*	
		*	@param	val Numero a almacenar
		*
		*	@param	grow Si el lugar no era suficiente, agrega mas
		*/
		void append( const unsigned int n, int val, bool grow = true );/* TODO ;*/

		/**
		*	@brief 	Agrega el contenido del OutputBitStream o al final del stream actual, alineado al proximo byte.
		*			Si no hay espacio suficiente para la cantidad de bits deseados
		*			se puede aumentar o no realizar operacion alguna.
		*
		*	@param	o Stream origen
		*
		*	@param	grow Si el lugar no era suficiente, agrega mas
		*/
		void append( OutputBitStream& o, bool grow = true );

		/** @brief Agrega una cadena al stream.
		 *
		 *  Agrega al stream los bytes del bloque de memoria s, hasta
		 *  que se encuentre un caracter nulo o se alcance el limite n.
		 *  El caracter nulo, de encontrarse, se coloca en el stream.
		 *  La cadena se coloca alineada al byte.
		 *
		 *  @param s Cadena a agregar, terminada en caracter nulo.
		 *  @param n Numero maximo de caracteres.
		 *  @param grow Define si es posible crecer.
		 */
		void append_string( const char* s, unsigned int n, bool grow=true );


		/**
		*
		*	@brief	Genera espacio en la parte mas baja del numero, desplazando
		*			todo hacia la izquierda
		*
		*	@param	Cantidad de bits a desplazar
		*/			
		void grow( unsigned int n );/* TODO ;*/
		
		/**
		*	@brief 	Permite obtener el contenido del stream. 
		*
		*	@return Un vector con el contenido
		*/
		unsigned const char* get_data();
		
		/**
		*
		*	@brief	Permite obtener la cantidad de bytes que posee el stream.
		*
		*	@return Cantidad de bytes
		*/
		unsigned int get_size();
	
		/**
		*	@brief	Permite calcular la cantidad de bits necesarios para un numero
		*
		*	@param	num Numero deseados
		*
		*	@return cantidad de bits necesarios apra el mismo
		*/
		static unsigned int bits_needed(unsigned int num);
		
		
		void skip();
};

#endif /* __OUTPUTBITSTREAM_H__ */
