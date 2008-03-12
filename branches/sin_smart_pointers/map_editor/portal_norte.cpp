//Header
#include "portal_norte.h"

/* CLASE PORTAL NORTE: Clase que representa un portal con orientacion NORTE. Hereda de Portal. */

/* Constructor: */

PortalNorte::PortalNorte (int pos_x, int pos_y) : Portal(pos_x, pos_y, PORTAL_HORIZ_ANCHO, PORTAL_HORIZ_ALTO, NORTE){
	//Realizo las conexiones con los elementos adyacentes
	S_ptr<Punto> conec1 (new Punto(pos_x, pos_y - 1));
	S_ptr<Punto> conec2 (new Punto(pos_x, pos_y + this->get_ancho()));
	
	this->set_posible_conexion(0,0, conec1);
	this->set_posible_conexion(0,2, conec2);
}

/* Get Ruta Imagen: */

char* PortalNorte::get_ruta_imagen(){
		return RUTA_PORTAL_NORTE;
}

/* Get Pos Simetrica: */

S_ptr<Punto> PortalNorte::get_pos_simetrica(Mapa* mapa){
		S_ptr<Punto> pos_simetrica;
		if (this->estoy_en_frontera(mapa))
			pos_simetrica = new Punto (mapa->get_alto() - 1, this->get_pos_y());
		return pos_simetrica;
}

/* Crear Simetrico: */

S_ptr<Elemento> PortalNorte::crear_simetrico (Mapa* mapa){
	//Cargo la pos del elem actual en un punto
	S_ptr<Punto> pos (new Punto(this->get_pos_x(), this->get_pos_y()));
	//Obtengo la pos simetrica
	S_ptr<Punto> pos_simetrica = get_pos_simetrica(mapa);
	//Creo un portal, con la pos y orientacion simetrica al actual
	S_ptr<Elemento> portal = new PortalSur(pos_simetrica->get_x(), pos_simetrica->get_y());
	//Devuelvo el portal
	return portal;
}

/* Estoy en frontera: */

bool PortalNorte::estoy_en_frontera(Mapa* mapa){
	if (this->get_pos_x() == 0)
		return true;
	else
		return false;
}

/* Conectar con Simetrico: */

void PortalNorte::conectar_con_simetrico(S_ptr<Elemento> instancia, S_ptr<Elemento> simetrico, Mapa* mapa){
	S_ptr<Punto> conec (new Punto(mapa->get_alto() - 1, this->get_pos_y() + 1)); //Teleport
	this->set_posible_conexion(0,1, conec);
	Portal::conectar_con_simetrico(instancia, simetrico, mapa);
}
