//Header
#ifndef Nivel_h_
#define Nivel_h_

//Incluyo las librerias necesarias
#include <editor/mapa.h>
#include <editor/definiciones.h>
#include <editor/elemento.h>
#include <editor/fab_elementos.h>
#include <common/smart_pointer.h>

using namespace std;

/* CLASE NIVEL: Esta clase representa un nivel, que contiene un mapa. El mismo permite agregar y quitar elementos
   estructurales y modificadores al mapa, y tambien controlar que tenga una sola componente conexa, marcando los
   casilleros que estan conectados. */

class Nivel {

	//Atributos
	private:
		string nombre; //Nombre del nivel, se usa despues para guardar en un xml con ese nombre.
		Mapa* mapa; //Referencia al mapa contenido en el nivel

	public:

	/* Constructor: Inicializa el nivel con un mapa con el ancho, alto y nombre pasado por parametro. */
	Nivel(string nombre, int ancho, int alto);

	/* Destructor: Libera los recursos consumidos por el nivel. */
	~Nivel();

	/* Agregar Elemento: Se encarga de crear un nuevo elemento estructural o modificador determinado por el tipo
	   pasado por parametro, en las posiciones posX, posY del mapa, con la orientacion pasada por parametro.
	   Si no se puede crear el elemento, o no se puede agregar al mapa en las posiciones determinadas devuelve false. Si se pudo agregar devuelve true. */
	bool agregar_elemento(TipoElem tipo, int posX, int posY, Orientacion orientacion);

	/* Quitar Elemento: Quita el elemento del mapa que se encuentra en posX, posY. 
	   Si el mismo contiene un elemento modificador remueve ese elemento, sin eliminar el estructural. Si solo contiene el elemento estructural lo elimina de todos los casilleros que este ocupa, junto con todos los elementos modificadores que posea.
	   Devuelve true si se pudo quitar el elemento, false en caso contrario. */
	bool quitar_elemento(int posX, int posY);

	/* Es Congruente: Devuelve true si el nivel es congruente (el mapa tiene una sola componente conexa), false en      caso contrario. */
	bool es_congruente();

	/* Get Mapa: Devuelve el mapa del nivel */
	Mapa* get_mapa();
	
	/* Set Nombre: Coloca un nuevo nombre pasado por parametro al nivel. */
	void set_nombre(string nombre);
	
	/* Get Nombre: Devuelve el nombre del nivel. */
	string get_nombre();
	
	/* ToXML: Guarda el nivel en un archivo xml con extension EXT_NIVEL, que lleva el formato: nombreArchivoMundo_nombreNivel + EXT_NIVEL.
	   Se pasa por parametro el nombre del archivo donde se guardo el mundo.
	   Devuelve true si se pudo guardar, false en caso contrario. */
	bool toXml(const char* filename_mundo);
	
	/* FromXML: Carga el nivel desde un archivo xml con extension EXT_NIVEL, que lleva el formato: nombreArchivoMundo_nombreNivel + EXT_NIVEL.
	   Se pasa por parametro el nombre del archivo donde se guardo el mundo.
	   Devuelve true si se pudo cargar, false en caso contrario. */
	bool fromXml(const char* filename_mundo);

};

#endif
