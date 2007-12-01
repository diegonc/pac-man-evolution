//Header
#ifndef Traductor_h_
#define Traductor_h_

#include "definiciones.h"
#include "../common/smart_pointer.h"
#include "mundo.h"
#include "../server/MundoBajoNivel.h"
#include "../server/MundoBasicImp.h"

/* CLASE TRADUCTOR: Clase que se encarga de traducir un mundo de alto nivel (del editor),
   a un mundo de bajo nivel (para el servidor). */

class Traductor {

	public:

	/* Traducir: Devuelve un nuevo mundo de bajo nivel, generado a partir del mundo de alto
	   nivel pasado por parametro. */
	MundoBajoNivel* traducir(Mundo* mundo);
	
	private:
		
	/* Traducir Mapa: Recibe un mapa de alto nivel y lo traduce a un mapa de bajo nivel, devolviendo
	   una referencia al mismo. */
	S_ptr<MapaBajoNivel> traducir_mapa (Mapa* mapa);
	
	/* Trad Cod Elemento: Traduce un codigo de elemento de alto nivel a un codigo de elemento de 
	   bajo nivel. */
	char trad_cod_elemento(TipoElem tipo);
	
	/* Realizar Conexiones: Dados un mapa de alto nivel y uno de bajo nivel cargados, realiza las
	   conexiones entre estructurales de bajo nivel, en el mapa de bajo nivel, basandose en el
	   de alto nivel. */
	void realizar_conexiones(Mapa* mapa, S_ptr<MapaBajoNivel> mapa_bajo_nivel);
	
};

#endif
