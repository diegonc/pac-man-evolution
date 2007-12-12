//Header
#include "casillero.h"

/* CLASE CASILLERO: Esta clase representa un casillero, que es la unidad espacial minima en el mapa. Cada casillero
   puede contener una parte de un elemento estructural y ademas un modificador. El casillero ademas tiene una 
   posicion x y una posicion y. */

/* Constructor: */

Casillero::Casillero(int pos_x, int pos_y){
	this->pos_x = pos_x;
	this->pos_y = pos_y;
}

/* Get Pos X: */

int Casillero::get_pos_x(){
	return this->pos_x;
}

/* Get Pos Y: */

int Casillero::get_pos_y(){
	return this->pos_y;
}

/* Get Estructural: */

S_ptr<Elemento> Casillero::get_estructural(){
	return this->estructural;
}

/* Get Modificador: */

S_ptr<Elemento> Casillero::get_modificador(){
	return this->modificador;
}

/* Tiene Modificador: */

bool Casillero::tiene_modificador(){
	if (this->modificador.es_nulo())
		return false;
	return true;
}

/* Agregar Elemento: */

bool Casillero::agregar_elemento(S_ptr<Elemento> elemento){
	bool result = true;
	if (!elemento.es_nulo()){
		if ((elemento->es_estructural()) && (this->estructural.es_nulo()))
			this->estructural = elemento;
		else
			if ((!elemento->es_estructural()) && (this->modificador.es_nulo()))
				this->modificador = elemento;
			else
				result = false;
	} else
		result = false;
	return result;
}

/* Remover Modificador: */

bool Casillero::remover_modificador(){
	if (!this->modificador.es_nulo()) {
		S_ptr<Elemento> elem_nulo;
		this->modificador = elem_nulo;
	} else
		return false;
	return true;
}

/* Remover Estructural: */

bool Casillero::remover_estructural(){
	if (!this->estructural.es_nulo()) {
		this->remover_modificador();
		S_ptr<Elemento> elem_nulo;
		this->estructural = elem_nulo;
	} else
		return false;
	return true;
}

/* //////////TEMPORAL////////// */
void Casillero::imprimir(){
	cout << "(" << this->pos_x << "," << this->pos_y << "): Estructural: ";
	if (!this->estructural.es_nulo()) {
		cout << this->estructural->toString();
		cout << " HABITABLE: "; 
		if (this->estructural->es_habitable(this->pos_x, this->pos_y))
			cout << "SI";
		else
			cout << "NO"; 
	}
	else
		cout << "NINGUNO";
	cout << '\n';
	cout << "Modificador: ";
	if (!this->modificador.es_nulo())
		cout << this->modificador->toString();
	else
		cout << "NINGUNO";
	cout << '\n';
}
