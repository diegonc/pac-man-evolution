//Header
#ifndef Traductor_h_
#define Traductor_h_

#include "../map_editor/definiciones.h"
#include "../map_editor/estructural.h"
#include "../map_editor/modificador.h"
#include "../map_editor/elemento.h"
#include "../map_editor/mundo.h"
#include "../common/smart_pointer.h"
#include "../common/MundoBajoNivel.h"
#include "../common/MundoBasicImp.h"
#include "../common/MapaBajoNivel.h"
#include "../common/MapImpSet.h"
#include "../common/EstructuralUnitarioFactory.h"
#include "../common/EstructuralPasillo.h"

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
	
	/* Conectar Casilleros: Conecta 2 estructurales de bajo nivel del mapa de bajo nivel, verificando si hay conexion entre los estructurales
	   de alto nivel contenidos en los casilleros origen y destino. La orientacion determina si el estructural destino esta al norte, sur, este u oeste
	   del origen.
	*/

	void conectar_casilleros(S_ptr<Casillero> origen, S_ptr<Casillero> destino, S_ptr<MapaBajoNivel> mapa_bajo_nivel, Orientacion orientacion);

};

#endif
