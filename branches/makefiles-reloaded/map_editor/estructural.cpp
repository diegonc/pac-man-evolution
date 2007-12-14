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
	if (this->contiene(x,y))
		return this->componentes[x_rel][y_rel]->es_pto_conexion();
	else
		return false;
}

/* Get Posible Conexion:  */

S_ptr<Punto> Estructural::get_posible_conexion(int x, int y){
	S_ptr<Punto> posib_conex;
	if (this->es_punto_conexion(x,y)){
		int x_rel = x - this->get_pos_x();
		int y_rel = y - this->get_pos_y();
		posib_conex = this->componentes[x_rel][y_rel]->get_posible_conexion();
	}
	return posib_conex;
}

/* Hay Conexion: */

bool Estructural::hay_conexion(int x1, int y1, int x2, int y2, Mapa* mapa){
	//Si evaluo 2 puntos que caen adentro del mismo estructural directamente digo q estan conectados
	if ((this->contiene(x1,y1)) && (this->contiene(x2,y2)))
		return true;
	else {
		//Si (x1,y1) es punto de conexion del elem actual
		if (this->es_punto_conexion(x1, y1)){
			S_ptr<Punto> posib_conex = this->get_posible_conexion(x1, y1);
			//Si la conexion se da con (x2,y2)
			if ((posib_conex->get_x() == x2) && (posib_conex->get_y() == y2)){
				//Obtengo el elem que se encuentra en el mapa en (x2,y2)
				S_ptr<Casillero> casillero = mapa->get_casillero(x2, y2);
				if (!casillero.es_nulo()){
					S_ptr<Elemento> otro_elem = casillero->get_estructural();
					if (!otro_elem.es_nulo()){
						if (otro_elem->es_punto_conexion(x2, y2)) {
							posib_conex = otro_elem->get_posible_conexion(x2, y2);
							//Si en el otro elem la conexion es con el primero devuelvo true, sino devuelvo false
							if ((posib_conex->get_x() == x1) && (posib_conex->get_y() == y1))
								return true;
							else
								return false;
						} else //Si hay otro elemento en (x2,y2) pero ese punto no es de conexion -> no hay conexion
							return false;
					} else //Si el elemento destino es nulo lo dejo como conexion
						return true;
				} else //Si el casillero al cual me quiero conectar es nulo devuelvo false
					return false;
			} else //Si la conexion de (x1,y1) no es con (x2, y2) devuelvo false
				return false;
		} else //Si no hay punto de conexion en (x1,y1) devuelvo false
			return false;
	}	
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
	bool result = true; //Vble aux
	list<S_ptr<Elemento> > elementos; //Lista para contener los elementos con los cuales conectarse
	int cont1 = 0; int cont2 = 0;
	//Recorro todo el elemento
	while ((result) && (cont1 < this->get_alto())){
		while ((result) && (cont2 < this->get_ancho())){
			//Si la componente es pto de conexion del elemento
			if (this->componentes[cont1][cont2]->es_pto_conexion()){
				//Obtengo la posible conexion
				S_ptr<Punto> posib_conex = this->componentes[cont1][cont2]->get_posible_conexion();
				//Pregunto si hay conexion entre el pto de conexion y la posible conexion
				if (this->hay_conexion(this->get_pos_x() + cont1, this->get_pos_y() + cont2, posib_conex->get_x(), posib_conex->get_y(), mapa)){
					//Si hay obtengo el elemento con el cual conectar, y si no es nulo lo agrego a la lista
					S_ptr<Elemento> elem = mapa->get_casillero(posib_conex->get_x(),posib_conex->get_y())->get_estructural();
					if (!elem.es_nulo())
						elementos.push_back(elem);
				} else
					result = false; //Si no hay conexion corto
			}
			cont2++;
		}
		cont1++;
		cont2 = 0;
	}
	//Si se pudieron efectuar todas las conexiones, las hago
	if (result) {
		list<S_ptr<Elemento> >::iterator it;
		for (it = elementos.begin(); it != elementos.end(); ++it)
			mapa->conectar(instancia, *it);
	}
	return result;
}

/* Quitate: */

void Estructural::quitate(S_ptr<Elemento> instancia, Mapa* mapa){
	for (int cont1 = 0; cont1 < this->get_alto(); cont1++)
		for (int cont2 = 0; cont2 < this->get_ancho(); cont2++){
			S_ptr<Elemento> modif = mapa->get_casillero(this->get_pos_x() + cont1 , this->get_pos_y() + cont2)->get_modificador();
			if (!modif.es_nulo()){
					modif->quitate(modif, mapa);
			}
		}
	mapa->quitar_elemento(instancia);
}
