//Header
#include "estructural.h"

/* CLASE ESTRUCTURAL: Esta clase abstracta representa un elemento estructural y desciende de elemento. */

/* Constructor: */

Estructural::Estructural(int pos_x, int pos_y, int ancho, int alto, Orientacion orientacion) : Elemento(pos_x, pos_y, ancho, alto, orientacion) {
	//Creo las filas de la matriz de componentes
	this->componentes = new S_ptr<Componente>* [this->get_alto()];
	//Por cada fila creo las columnas
	for (int i = 0; i < this->get_alto(); i++)
		this->componentes[i] = new S_ptr<Componente> [this->get_ancho()];
	//Creo los componentes
	for (int i = 0; i < this->get_alto(); i++)
		for (int j = 0; j < this->get_ancho(); j++){
			S_ptr<Componente> ptr_componente (new Componente());
			this->componentes[i][j] = ptr_componente;
		}
}

/* Set Habitable: */

void Estructural::set_habitable (int pos_x, int pos_y, bool habitable){
	this->componentes[pos_x][pos_y]->set_habitable(habitable);
}

/* Set Posible Conexion: */

void Estructural::set_posible_conexion (int pos_x, int pos_y, S_ptr<Punto> posib_conex){
	this->componentes[pos_x][pos_y]->set_posible_conexion(posib_conex);
}

/* Destructor: */

Estructural::~Estructural(){
	//Por cada fila elimino las columnas
	for (int i = 0; i < this->get_alto(); i++)
		delete[](this->componentes[i]);
	//Elimino las filas
	delete[](this->componentes);
}

/* Es Estructural: */

bool Estructural::es_estructural(){
	return true;
}

/* Es Punto Conexion: */

bool Estructural::es_punto_conexion(int x, int y){
	int x_rel = x - this->get_pos_x();
	int y_rel = y - this->get_pos_y();
	if ((x_rel >= 0) && (x_rel < this->get_alto()) && (y_rel >= 0) && (y_rel < this->get_ancho()))
		return this->componentes[x_rel][y_rel]->es_pto_conexion();
	else
		return false;
}

/* Hay Conexion: */

bool Estructural::hay_conexion(int x1, int y1, int x2, int y2){
	int x_rel = x1 - this->get_pos_x();
	int y_rel = y1 - this->get_pos_y();
	if (this->es_punto_conexion(x1, y1)){
		S_ptr<Punto> posib_conex = this->componentes[x_rel][y_rel]->get_posible_conexion();
		if ((posib_conex->get_x() == x2) && (posib_conex->get_y() == y2))
			return true;
		else
			return false;
	} else
		return false;	
}

/* Es Habitable: */

bool Estructural::es_habitable(int x, int y){
	int x_rel = x - this->get_pos_x();
	int y_rel = y - this->get_pos_y();
	if ((x_rel >= 0) && (x_rel < this->get_alto()) && (y_rel >= 0) && (y_rel < this->get_ancho()))
		return this->componentes[x_rel][y_rel]->es_habitable();
	else
		return false;
}

/* Agregate: */

bool Estructural::agregate(S_ptr<Elemento> instancia, Mapa* mapa) {
	bool result = true;
	result = mapa->superficie_disponible(this->get_pos_x(), this->get_pos_y(), this->get_alto(), this->get_ancho());
	if (result) {
		mapa->insertar_elemento(instancia);
		result = this->conectar(instancia, mapa);
		if (!result) mapa->quitar_elemento(instancia);
	}
	return result;
}

/* Conectar: */

bool Estructural::conectar(S_ptr<Elemento> instancia, Mapa* mapa) {
	bool result = true;
	list<S_ptr<Elemento> > elementos;
	int cont1 = 0; int cont2 = 0;
	while ((result) && (cont1 < this->get_alto())){
		while ((result) && (cont2 < this->get_ancho())){
			if (this->componentes[cont1][cont2]->es_pto_conexion()){
				S_ptr<Punto> posib_conex = this->componentes[cont1][cont2]->get_posible_conexion();
				S_ptr<Casillero> casillero = mapa->get_casillero(posib_conex->get_x(),
				posib_conex->get_y());
				if (!casillero.es_nulo()){
					S_ptr<Elemento> elem = casillero->get_estructural();
					if (!elem.es_nulo()) {
						if (elem->hay_conexion(posib_conex->get_x(), posib_conex->get_y(), this->get_pos_x(), this->get_pos_y()))
							elementos.push_back(elem);
						else
							result = false;
					}
				} else
					result = false;
			}
			cont2++;
		}
		cont1++;
		cont2 = 0;
	}
	if (result) {
		list<S_ptr<Elemento> >::iterator it;
		for (it = elementos.begin(); it != elementos.end(); ++it)
			mapa->conectar(instancia, *it);
	}
	return result;
}
