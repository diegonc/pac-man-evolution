//Header
#include "nivel.h"

/* CLASE NIVEL: Esta clase representa un nivel, que contiene un mapa. El mismo permite agregar y quitar elementos
   estructurales y modificadores al mapa, y tambien controlar que tenga una sola componente conexa, marcando los
   casilleros que estan conectados. */

/* Constructor: */

Nivel::Nivel(int ancho, int alto){
	this->mapa = new Mapa(ancho, alto);
}

/* Destructor: */

Nivel::~Nivel(){
	delete(this->mapa);
}

/* Agregar Elemento: */

bool Nivel::agregar_elemento(TipoElem tipo, int posX, int posY, Orientacion orientacion){
	bool result = true;
	//Si las posiciones recibidas estan dentro de los margenes del mapa agrego el elemento
	if ((posX >= 0) && (posY >= 0) && (posX < this->mapa->get_ancho()) && (posY < this->mapa->get_alto())){
		S_ptr<Fab_Elementos> fabrica (new Fab_Elementos());
		S_ptr<Elemento> elemento = fabrica->construir(tipo, posX, posY, orientacion);
		if (!elemento.es_nulo())
			result = elemento->agregate(elemento, this->mapa);
		else
			result = false;
	} else
		result = false;
	return result;
}

/* Quitar Elemento: */

bool Nivel::quitar_elemento(int posX, int posY){
	bool result = true;
	//Si las posiciones recibidas estan dentro de los margenes del mapa quito el elemento
	if ((posX >= 0) && (posY >= 0) && (posX < this->mapa->get_ancho()) && (posY < this->mapa->get_alto())){
		S_ptr<Casillero> casillero = this->mapa->get_casillero(posX, posY);
		S_ptr<Elemento> elemento;
		if (casillero->tiene_modificador())
			elemento = casillero->get_modificador();
		else
			elemento = casillero->get_estructural();
		if (!elemento.es_nulo())
			elemento->quitate(elemento, this->mapa);
	} else
		result = false;
	return result;
}

/* Es Congruente: */

bool Nivel::es_congruente(){
	return this->mapa->es_congruente();
}

/* Get Mapa: */

Mapa* Nivel::get_mapa(){
	return this->mapa;
}

/* /////////////TEMPORAL////////////// */
void Nivel::imprimir_mapa(){
	this->mapa->imprimir();
}
