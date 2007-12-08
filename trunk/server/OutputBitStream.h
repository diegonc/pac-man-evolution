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
