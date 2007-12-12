//Header
#ifndef Mundo_h_
#define Mundo_h_

//Incluyo las librerias necesarias
#include "nivel.h"
#include "definiciones.h"
#include <list>
#include "../common/smart_pointer.h"
#include "../common/observable.h"

using namespace std;

/* CLASE MUNDO: Esta clase representa el mundo, compuesto por niveles. El mismo permite insertar o quitar nuevos
   niveles, reordenarlos, e insertar o quitar elementos estructurales y modificadores en un mapa determinado. */

class Mundo : public Observable {

	//Atributos
	private:
		list<S_ptr<Nivel> > niveles; //Vector de niveles. Su orden determina la progresion de los mismos.

	public:

	/* Constructor: Inicializa el mundo sin niveles. */
	Mundo();

	/* Destructor: Libera los recursos consumidos por el mundo. */
	~Mundo();

	/* Agregar Nivel: Crea un nuevo nivel vacio con el ancho, alto y nombre pasados por parametros, 
	   y lo agrega al final de la lista de niveles (como ultimo nivel).
	   Devuelve el numero de orden dentro de la lista de niveles o -1 si hubo error. */
	int agregar_nivel(string nombre, int ancho, int alto);

	/* Quitar Nivel: Quita el nivel que tiene como numero de orden el pasado por parametro. Si no lo encuentra
	   no hace nada */
	void quitar_nivel(unsigned int nOrden);

	/* Agregar Elemento: Se encarga de crear un nuevo elemento estructural o modificador determinado por el tipo
	   pasado por parametro, al mapa contenido en el nivel cuyo orden es nOrden, en el casillero que se encuentra en
	   las coordenadas posX, posY, con la orientacion pasada por parametro.
	   Si no se puede crear el elemento, o no se puede agregar al mapa en las posiciones determinadas devuelve
	   false. Si se pudo agregar devuelve true. */
	bool agregar_elemento(TipoElem tipo, unsigned int nOrden, int posX, int posY, Orientacion orientacion);

	/* Quitar Elemento: Quita el elemento contenido en el mapa del nivel cuyo orden es nOrden, en el casillero que
	   se encuentra en posX, posY. Si el mismo contiene un elemento modificador remueve ese elemento, sin eliminar
	   el estructural. Si solo contiene el elemento estructural lo elimina de todos los casilleros que este ocupa,
           junto con todos los elementos modificadores que posea.
	   Devuelve true si se pudo quitar el elemento, false en caso contrario. */
	bool quitar_elemento(unsigned int nOrden, int posX, int posY);
	
	/* Get Nivel: Devuelve el nivel cuyo numero de orden es nOrden. Si el orden es incorrecto devuelve un nivel nulo. */
	S_ptr<Nivel> get_nivel(unsigned int nOrden);
	
	/* Get Nivel Por Nombre: Devuelve el nivel cuyo nombre coincide con el pasado por parametro. Si no lo encuentra
	   devuelve un nivel nulo. */
	S_ptr<Nivel> get_nivel_por_nombre(string nombre);

	/* Promover: Disminuye en 1 el orden del nivel cuyo numero actual de orden es nOrden, colocandolo mas cerca
	   del principio de la lista. Si es el primero no hace nada */
	void promover(unsigned int nOrden);

	/* Degradar: Aumenta en 1 el orden del nivel cuyo numero actual de orden es nOrden, colocandolo mas lejos
	   del principio de la lista. Si es el ultimo no hace nada */
	void degradar(unsigned int nOrden);
	
	/* Get Cant Niveles: Devuelve la cantidad de niveles del mundo. */
	unsigned int get_cant_niveles();
	
	/* Chequear mundo: Chequea nivel por nivel hasta que uno sea incorrecto y carga un numero del nivel con error
					   y devuelve el codigo de error : - 0 si el mundo es correcto
								  			  		   - 1 si el error es que el nivel no tiene salida de pacman
								  			  		   - 2 si el error es que el nivel no tiene casa de fantasmas
								  			  		   - 3 si el nivel no tiene una unica componente conexa.
		Devuelve -1 como numero de nivel incorrecto, si todos son correctos. */
	char chequear_mundo(int &N_Nivel_incorrecto);
	
	/* ToXML: Guarda el mundo y todos sus niveles en archivos de la extension adecuada. Se debe pasar por parametro el nombre del archivo
	   donde guardar la info del mundo.
	   Devuelve true si se pudo guardar, false en caso contrario. */
	bool toXml(char* nombre);
	
	/* fromXML: Carga el mundo con todos sus niveles desde el un archivo cuyo nombre se pasa por parametro.
	   Devuelve true si pudo cargar, false en caso contrario. */
	bool fromXml(char* nombre);

};

#endif
