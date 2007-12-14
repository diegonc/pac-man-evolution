//Header
#include "portal_oeste.h"

/* CLASE PORTAL OESTE: Clase que representa un portal con orientacion OESTE. Hereda de Portal. */

/* Constructor: */

PortalOeste::PortalOeste (int pos_x, int pos_y) : Portal(pos_x, pos_y, PORTAL_VERT_ANCHO, PORTAL_VERT_ALTO, OESTE){
	
	S_ptr<Punto> conec1 (new Punto(pos_x + 1, this->mapa->get_ancho() - 1)); //Teleport
	S_ptr<Punto> conec2 (new Punto(pos_x - 1, pos_y));
	S_ptr<Punto> conec3 (new Punto(pos_x + this->get_alto(), pos_y));
	
	this->set_posible_conexion(1,0,conec1);
	this->set_posible_conexion(0,0, conec2);
	this->set_posible_conexion(2,0, conec3);
}

/* Get Ruta Imagen: */

char* PortalOeste::get_ruta_imagen(){
		return RUTA_PORTAL_OESTE;
}

/* Get Pos Simetrica: */

S_ptr<Punto> PortalOeste::get_pos_simetrica(Mapa* mapa){
		S_ptr<Punto> pos_simetrica;
		if (this->estoy_en_frontera(mapa))
			pos_simetrica = new Punto (this->get_pos_x(), mapa->get_ancho() - 1);
		return pos_simetrica;
}

/* Crear Simetrico: */

S_ptr<Elemento> PortalOeste::crear_simetrico (Mapa* mapa){
	//Cargo la pos del elem actual en un punto
	S_ptr<Punto> pos (new Punto(this->get_pos_x(), this->get_pos_y()));
	//Obtengo la pos simetrica
	S_ptr<Punto> pos_simetrica = get_pos_simetrica(mapa);
	//Creo un portal, con la pos y orientacion simetrica al actual
	S_ptr<Elemento> portal = new PortalEste(pos_simetrica->get_x(), pos_simetrica->get_y());
	//Devuelvo el portal
	return portal;
}

/* Estoy en frontera: */

bool PortalOeste::estoy_en_frontera(Mapa* mapa){
	if (this->get_pos_y() == 0)
		return true;
	else
		return false;
}
