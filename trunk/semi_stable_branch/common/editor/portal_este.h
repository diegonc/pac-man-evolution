//Header
#ifndef Portal_Este_h_
#define Portal_Este_h_

//Incluyo las librerias necesarias
#include <editor/portal.h>
#include <editor/portal_oeste.h>
#include <editor/punto.h>

/* CLASE PORTAL ESTE: Clase que representa un portal con orientacion ESTE. Hereda de Portal. */

class PortalEste : public Portal {

	public:

	/* Constructor: Inicializa un portal con las posiciones pasadas por parametros. */
	PortalEste (int pos_x, int pos_y);

	/* Get Ruta Imagen: Devuelve una cadena con la ruta donde se encuentra la imagen que representa al elemento */
	virtual char* get_ruta_imagen();
	
	private:
	
	/* Conectar con Simetrico: Establece un punto de conexion con el elemento simetrico en el mapa pasado
	   por param. */
	virtual void conectar_con_simetrico(S_ptr<Elemento> instancia, S_ptr<Elemento> simetrico, Mapa* mapa);
	
	/* Get Pos Simetrica: Devuelve la pos simetrica del elem actual, respecto del mapa pasado por param. 
	   Si el elemento no se encuentra en el limite del mapa devuelve null. */
	virtual S_ptr<Punto> get_pos_simetrica(Mapa* mapa);
	
	/* Crear Simetrico: Devuelve un nuevo portal simetrico al actual. 
	   Calcula su pos de acuerdo a la pos del elemento actual y el mapa pasado por parametro. */
	virtual S_ptr<Elemento> crear_simetrico (Mapa* mapa);
	
	/* Estoy en frontera: Devuelve true si el portal esta en la frontera correcta del mapa, false en caso
	   contrario. */
	virtual bool estoy_en_frontera(Mapa* mapa);

};

#endif
