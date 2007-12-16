#ifndef __CONFVALUE_H__
#define __CONFVALUE_H__

#include <string>
#include <iostream>

/** @brief Valor de configuracion.
 *
 *  Representa un valor de configuracion. El tipo del valor puede ser
 *    - Entero
 *    - Boleano
 *    - Cadena de texto 
 */
class ConfValue
{
	//public:
		/** Enumera los tipos soportados. */
		enum Tipo { CV_NULO, CV_TEXTO, CV_NUMERO, CV_BOOL };

	private:
		/** Tipo de dato del valor. */
		ConfValue::Tipo tipo;

		union {
			std::string*	cadena;
			int		numero;
			bool		booleano;
		};

	public:
		/** @brief Constructor por defecto.(requerido por std::map) */
		ConfValue( ) : tipo( CV_NULO ){ }

		/** @brief Crea un valor de configuracion de tipo NUMERO. */
		ConfValue( int valor );

		/** @brief Crea un valor de configuracion de tipo TEXTO. */
		ConfValue( std::string valor );

		/** @brief Crea un valor de configuracion de tipo BOOL. */
		ConfValue( bool valor );

		ConfValue( const ConfValue& cv );

		~ConfValue();

		ConfValue& operator=( const ConfValue& cv );

		/** @brief Obtiene el valor de la configuracion de tipo
		 *  NUMERO.
		 */
		int get_numero() const;

		/** @brief Obtiene el valor de la configuracion de tipo
		 *  TEXTO.
		 */
		std::string get_texto() const;

		/** @brief Obtiene el valor de la configuracion de tipo
		 *  BOOL.
		 */
		bool get_booleano() const;

		bool operator==( const ConfValue& otro ) const;

		void dump( std::ostream& out ) const;
};

#endif
