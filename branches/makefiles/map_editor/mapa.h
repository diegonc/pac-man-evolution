//Header
#ifndef Mapa_h_
#define Mapa_h_

//Incluyo las librerias necesarias
#include "casillero.h"
#include "elemento.h"
#include "dato_vertice.h"
#include "recorredor_grafo.h"
#include "../common/tinyxml/tinyxml.h"
#include "../common/smart_pointer.h"
#include "../common/grafo.h"
#include "../common/vertice.h"
#include "../common/arco.h"
#include "../common/wrapper.h"
#include "obj_nulo.h"
#include <list>

class Elemento;
class Casillero;
class DatoVertice;

using namespace std;

/* CLASE MAPA: Esta clase representa un mapa, compuesto de casilleros. Un mapa ademas posee un grafo de conexiones
   entre los elementos estructurales que se encuentran en el mismo. */

class Mapa {

	//Atributos
	private:
		int ancho; //Cantidad de cols
		int alto; //Cantidad de filas
		S_ptr<Casillero>** mapa; //Matriz de casilleros que conforman al mapa
		Grafo<Wrapper<DatoVertice>, Obj_Nulo>* conexiones; //Grafo que contiene las conexiones entre los elementos estructurales
		RecorredorGrafo<Wrapper<DatoVertice>, Obj_Nulo>* recorredor; //Objeto que se encarga de recorrer el grafo de conexiones para encontrar los vertices desconectados
		list<S_ptr<Elemento> > elementos; //Lista que contiene los elementos del mapa
		list<S_ptr<Elemento> > desconectados; //Lista que contiene los elementos desconectados
		bool salida; //Booleano que controla si el mapa tiene o no salida de pacman
		bool casa; //Booleano que controla si el mapa tiene o no casa de fantasmas
	
	public:

	/* Constructor: Inicializa el mapa con el ancho y alto pasado por parametro. */
	Mapa(int ancho, int alto);

	/* Destructor: Libera los recursos consumidos por el mapa. */
	~Mapa();

	/* Get Ancho: Devuelve el ancho del mapa. */
	int get_ancho();
	
	/* Get Alto: Devuelve el alto del mapa. */
	int get_alto();

	/* Insertar Elemento: Agrega el elemento pasado por parametro al mapa en todos los casilleros que este
	   ocupe. No realiza ningun tipo de validacion. */
	void insertar_elemento(S_ptr<Elemento> elemento);

	/* Quitar Elemento: Quita el elemento pasado por parametro del mapa (lo saca de todos los casilleros que
	   este ocupe). No realiza ningun tipo de validacion. */
	void quitar_elemento(S_ptr<Elemento> elemento);
	
	/* Get Elementos: Devuelve una lista con los elementos contenidos en el mapa. */
	list<S_ptr<Elemento> >& get_elementos();

	/* Es Congruente: Devuelve true si el mapa es congruente (tiene una sola componente conexa), false en caso
	   contrario. */
	bool es_congruente();

	/* Get Casillero: Devuelve un puntero al casillero que se encuentra en las posiciones pasadas por parametro.
	   Si las mimas son invalidas devuelve NULL. */
	S_ptr<Casillero> get_casillero(int pos_x, int pos_y);

	/* Conectar: Busca los 2 elementos pasados por parametro en el mapa y si los encuentra los conecta */
	void conectar(S_ptr<Elemento> elem1, S_ptr<Elemento> elem2);

	/* Get Desconectados: Metodo que se encarga de encontrar todos los elementos desconectados de la componente
	   conexa a la cual pertenece el elemento mas antiguo del mapa.	*/
	list<S_ptr<Elemento> >& get_desconectados();

	/* Validar Coordenadas: Recibe coordenadas (x, y), y devuelve true si estan dentro del mapa, false en caso
	   contrario */
	bool validar_coordenadas(int x, int y);

	/* Superficie Disponible: Dados un (x,y) coords superior izq de la superficie, y un ancho y alto de la misma,
	   devuelve true si en el mapa esa superficie esta libre de elementos, false en caso contrario */
	bool superficie_disponible(int x, int y, int alto, int ancho);
	
	/* Set Salida: Setea el estado al mapa, si tiene o no salida de pacman */
	void set_salida(bool estado);
	
	/* Tiene Salida: Devuelve true si el mapa tiene salida de pacman, false en caso contrario */
	bool tiene_salida();
	
	/* Set Casa Fantasmas: Setea el estado al mapa, si tiene o no casa de fantasmas */
	void set_casa_fantasmas(bool estado);
	
	/* Tiene Casa Fantasmas: Devuelve true si el mapa tiene casa de fantasmas, false en caso contrario */
	bool tiene_casa_fantasmas();

	/* ToXML: Devuelve un elemento xml que contiene la representacion del mapa y todos sus casilleros.
	   Si hubo un error devuelve NULL. */
	S_ptr<TiXmlElement> toXml();

};

#endif
