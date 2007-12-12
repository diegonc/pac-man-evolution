#ifndef __CONFVALUE_H__
#define __CONFVALUE_H__

/** @brief Valor de configuracion.
 *
 *  Representa un valor de configuracion. El tipo del valor puede ser
 *    - Entero
 *    - Boleano
 *    - Cadena de texto ( estilo C )
 */
class ConfValue
{
	private:
		/** Tipo de dato del valor. */
		Tipo tipo;

		union {
			char*	cadena;
			int	numero;
			bool	booleano;
		} valor;

	public:
		/** Enumera los tipos soportados. */
		enum Tipo
		{
			TEXTO,
			NUMERO,
			BOOL
		};

		/** @brief Crea un valor de configuracion de tipo NUMERO. */
		ConfValue( int valor );

		/** @brief Crea un valor de configuracion de tipo TEXTO. */
		ConfValue( char* valor );

		/** @brief Crea un valor de configuracion de tipo BOOL. */
		ConfValue( bool valor );

		/** @brief Obtiene el valor de la configuracion de tipo
		 *  NUMERO.
		 */
		int get_numero();

		/** @brief Obtiene el valor de la configuracion de tipo
		 *  TEXTO.
		 */
		char* get_texto();

		/** @brief Obtiene el valor de la configuracion de tipo
		 *  BOOL.
		 */
		bool get_booleano();

};

#endif