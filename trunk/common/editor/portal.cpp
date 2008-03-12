//Header
#include <editor/portal.h>

/* CLASE PORTAL: Clase que representa un portal en una orientacion determinada. Hereda de estructural. */

/* Constructor: */

Portal::Portal(int pos_x, int pos_y, int ancho, int alto, Orientacion orientacion) : Estructural(pos_x, pos_y, ancho, alto, orientacion) {
	this->estoy_agregado = false;
}

/* Agregate: */

bool Portal::agregate(S_ptr<Elemento> instancia, Mapa* mapa){
	bool result;
	//Si el portal se agrega en el limite del mapa y no esta agregado ya
	if ((!this->estoy_agregado)
		&& (this->estoy_en_frontera(mapa))){
			//Intento agregar al elemento
			result = Estructural::agregate(instancia, mapa);
			//Si se pudo agregar intento agregar al simetrico
			if (result){
				this->estoy_agregado = true;
				result = this->agregar_simetrico(mapa);
				//Si no se pudo agregar al simetrico quito al elem actual
				if (!result)
					this->quitate(instancia, mapa);
				else { //Si se encontro al elem simetrico, realizo conexion
					S_ptr<Elemento> elem_simetrico = this->get_simetrico(mapa);
					this->conectar_con_simetrico(instancia, elem_simetrico, mapa);
				}
			}
	} else //Sino devuelve falso
		result = false;	
	return result;
}

/* Quitate: */

void Portal::quitate(S_ptr<Elemento> instancia, Mapa* mapa){
	//Si el portal esta agregado lo quito
	if (this->estoy_agregado){
		//Quito al elemento del mapa
		Estructural::quitate(instancia, mapa);
		//Quito al simetrico del mapa
		this->quitar_simetrico(mapa);
		this->estoy_agregado = false;
	}
}

/* Get Tipo: */

TipoElem Portal::get_tipo(){
	return PORTAL;
}

/* Get Simetrico: */

S_ptr<Elemento> Portal::get_simetrico(Mapa* mapa){
	//Cargo la pos del elem actual en un punto
	S_ptr<Punto> pos (new Punto(this->get_pos_x(), this->get_pos_y()));
	//Obtengo la pos simetrica
	S_ptr<Punto> pos_simetrica = get_pos_simetrica(mapa);
	//Obtengo el elem simetrico
	S_ptr<Elemento> elem_simetrico = mapa->get_casillero(pos_simetrica->get_x(), pos_simetrica->get_y())->get_estructural();;
	return elem_simetrico; // Lo devuelvo
}

/* Agregar Simetrico: */

bool Portal::agregar_simetrico(Mapa* mapa) {
	bool result;
	//Pido el elem simetrico
	S_ptr<Elemento> elem_simetrico = this->get_simetrico(mapa);
	//Si el simetrico es nulo, lo creo y lo agrego al mapa
	if (elem_simetrico.es_nulo()) {
		//Creo el elem simetrico
		elem_simetrico = this->crear_simetrico(mapa);
		//Lo agrego al mapa pasado por param. Si se pudo agregar result queda en true.
		//Sino queda en false.
		result = elem_simetrico->agregate(elem_simetrico, mapa);
	} else { //Si hay simetrico
		//Si es un portal es porque ya estaba agregado
		if (elem_simetrico->get_tipo() == PORTAL)
			result = true;
		else
			result = false; //Si existia el simetrico pero no es un portal entonces no se pudo agregar
	}
	return result;
}

/* Conectar con Simetrico: */

void Portal::conectar_con_simetrico(S_ptr<Elemento> instancia, S_ptr<Elemento> simetrico, Mapa* mapa){
		mapa->conectar(instancia, simetrico);
}

/* Quitar Simetrico: */

void Portal::quitar_simetrico(Mapa* mapa){
	//Obtengo el elem simetrico
	S_ptr<Elemento> elem_simetrico = this->get_simetrico(mapa);
	//Si el elemento no es nulo y es un portal lo quito del mapa
	if ((!elem_simetrico.es_nulo()) && (elem_simetrico->get_tipo() == PORTAL))
		elem_simetrico->quitate(elem_simetrico, mapa);
}
