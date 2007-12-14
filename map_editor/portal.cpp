//Header
#include "portal.h"

/* CLASE PORTAL: Clase que representa un portal en una orientacion determinada. Hereda de estructural. */

/* Constructor: */

Portal::Portal(int pos_x, int pos_y, int ancho, int alto, Orientacion orientacion) : Estructural(pos_x, pos_y, ancho, alto, orientacion) {
	this->estoy_agregado = false;
	this->mapa = NULL;
}

/* Agregate: */

bool Portal::agregate(S_ptr<Elemento> instancia, Mapa* mapa){
	bool result;
	//Si el portal se agrega en el limite del mapa y no esta agregado ya
	if ((!this->estoy_agregado)
		&& (this->estoy_en_frontera(mapa))){
			this->mapa = mapa;
			//Intento agregar al elemento
			cout << "asd1" << endl << flush;
			result = Estructural::agregate(instancia, mapa);
			//Si se pudo agregar intento agregar al simetrico
			if (result){
				cout << "asd2" << endl << flush;
				result = this->agregar_simetrico(mapa);
				cout << "asd3" << endl << flush;
				//Si no se pudo agregar al simetrico quito al elem actual
				if (!result) {
					this->quitate(instancia, mapa);
					this->mapa = NULL;
					cout << "asd4" << endl << flush;
				}
				cout << "asd5" << endl << flush;
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
		this->mapa = NULL;
	}
}

/* Get Tipo: */

TipoElem Portal::get_tipo(){
	return PORTAL;
}

/* Agregar Simetrico: */

bool Portal::agregar_simetrico(Mapa* mapa) {
	bool result;
	//Creo el elem simetrico
	S_ptr<Elemento> elem_simetrico = this->crear_simetrico(mapa);
	//Lo agrego al mapa pasado por param
	result = elem_simetrico->agregate(elem_simetrico, mapa);
	return result;
}
	
/* Quitar Simetrico: */

void Portal::quitar_simetrico(Mapa* mapa){
	//Cargo la pos del elem actual en un punto
	S_ptr<Punto> pos (new Punto(this->get_pos_x(), this->get_pos_y()));
	//Obtengo la pos simetrica
	S_ptr<Punto> pos_simetrica = get_pos_simetrica(mapa);
	//Obtengo el elem simetrico
	S_ptr<Elemento> elem_simetrico = mapa->get_casillero(pos_simetrica->get_x(), pos_simetrica->get_y())->get_estructural();
	//Si el elemento no es nulo lo quito del mapa
	if (!elem_simetrico.es_nulo())
		elem_simetrico->quitate(elem_simetrico, mapa);
}
