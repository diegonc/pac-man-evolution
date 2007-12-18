#ifndef __DATASTORE_H__
#define __DATASTORE_H__

/** @brief Interfaz para el acceso a la informacion del juego desde el cliente.
 *
 *  Luego de analizar la informacion proveniente de la red, los datos se hacen
 *  accesibles almacenandolos en una estructura que responde a esta interfaz.
 *
 *  En principio, a cada objeto del juego, el servidor le asignara un
 *  identificador numerico. Y esta interfaz posibilita el acceso a sus
 *  propiedades a traves de este identificador.
 *
 *  Ya que los identificadores son enviados por el servidor y el cliente los
 *  desconoce inicialmente, se proporciona el metodo for_each para que los
 *  usuarios de la "base de datos" puedan ser notificados de los
 *  identificadores disponibles.
 *
 *  Las propiedades de cada objeto se acceden a traves de metodos con firma
 *  similar a
 *  		Tipo get_'propiedad'( unsigned int id );
 *
 *  Caso de uso.
 *
 *  A continuacion se muestra una posible utilizacion de la interfaz.
 *
 *  --TODO: Creo haber leido por ahi que no era buena idea poner codigo en
 *          comentarios de doxygen. Por ahora lo mando aca. --
 *  --TODO: Tag para codigo??? --
 *  <code>
 *  class SomeCallBack
 *  {
 *      public:
 *          void operator()( const DataStore& store, unsigned int id )
 *          {
 *              std::cout << "Objeto con id " << id << " se encuentra en";
 *              std::cout << " x = " << store.get_x( id ) << " y = ";
 *              std::cout << store.get_y( id ) << std::endl;
 *          }
 *  };
 *
 *  const DataStore& ds;
 *  
 *  ds.for_each( SomeCallBack() );
 *  </code>
 *
 *  La inicializacion de la referencia se deja sin especificar hasta que se
 *  defina. La implementacion boba podria ser inicializada con facilidad
 *  empleando el constructor por defecto.
 */
class DataStore
{
	public:
		/** @brief Callback para el metodo DataStore::for_each
		 *
		 * Permite especificar la operacion que se ejecuta sobre
		 * cada elemento de un DataStore por medio de la herencia,
		 * empleando esta clase como base.
		 */
		class CallBack
		{
			public:
				virtual ~CallBack() { }

				/** @brief Operacion a aplicar.
				 *
				 *  El metodo DataStore::for_each invoca este
				 *  operador pasando por agumentos el
				 *  identificador de cada elemento disponible.
				 *
				 *  @param ds DataStore en la que se encuentra el elemento.
				 *            La existencia de este parametro permite la utilizacion
				 *            de un mismo callback en diferentes stores.
				 *  @param id Identificador del elemento actual.
				 */
				virtual void operator()( const DataStore& ds, unsigned int id ) = 0;
		};

		/** @brief Acceso masivo a los elementos.
		 *
		 *  @param cb Objeto ejecutable que se corre para cada elemento.
		 */
		virtual void for_each( const CallBack& cb ) = 0;

		/** @brief Acceso a propiedades de un elemento particular.
		 *
		 *  @param id Identificador del elemento.
		 */
		virtual /*indefinido*/ int get_x( unsigned int id ) = 0;

		/** @brief Acceso a propiedades de un elemento particular.
		 *
		 *  @param id Identificador del elemento.
		 */
		virtual /*indefinido*/ int get_y( unsigned int id ) = 0;
};

#endif /* __DATASTORE_H__ */

