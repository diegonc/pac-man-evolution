//Header
#include "mapa.h"

/* CLASE MAPA: Esta clase representa un mapa, compuesto de casilleros. Un mapa ademas posee un grafo de conexiones
   entre los elementos estructurales que se encuentran en el mismo. */

/* Constructor: */

Mapa::Mapa(int ancho, int alto){
	if ((ancho > 0) && (alto > 0)){
		this->ancho = ancho;
		this->alto = alto;
		//Creo las filas
		this->mapa = new S_ptr<Casillero>* [alto];
		//Por cada fila creo las columnas
		for (int i = 0; i < alto; i++)
			this->mapa[i] = new S_ptr<Casillero> [ancho];
		//Creo los casilleros vacios
		for (int i = 0; i < alto; i++)
			for (int j = 0; j < ancho; j++){
				S_ptr<Casillero> ptr_casillero (new Casillero(i, j));
				this->mapa[i][j] = ptr_casillero;
			}
	} else {
		this->mapa = NULL;
		this->ancho = 0;
		this->alto = 0;
	}
	//Creo el grafo de conexiones
	this->conexiones = new Grafo<S_ptr<Elemento>, Obj_Nulo>();
}

/* Destructor: */

Mapa::~Mapa(){
	//Por cada fila elimino las columnas
	for (int i = 0; i < alto; i++)
		delete[](this->mapa[i]);
	//Elimino las filas
	delete[](this->mapa);
	//Elimino el grafo de conexiones
	delete(this->conexiones);
	this->elementos.clear(); //Vacio la lista de elementos
}

/* Get Ancho: */

int Mapa::get_ancho(){
	return this->ancho;
}

/* Get Alto: */

int Mapa::get_alto(){
	return this->alto;
}

/* Insertar Elemento: */

void Mapa::insertar_elemento(S_ptr<Elemento> elemento){
	//Obtengo la posicion del elemento y su tamaño
	int pos_x = elemento->get_pos_x();
	int pos_y = elemento->get_pos_y();
	int e_ancho = elemento->get_ancho();
	int e_alto = elemento->get_alto();
	int cont1 = 0; int cont2 = 0;
	//Recorro todos los casilleros que ocupa el elemento y lo agrego a cada uno de ellos
	S_ptr<Casillero> casillero = this->get_casillero(pos_x, pos_y);
	while ((!casillero.es_nulo()) && (cont1 < e_alto)){
		while ((!casillero.es_nulo()) && (cont2 < e_ancho)){
			casillero->agregar_elemento(elemento);
			cont2++;
			casillero = this->get_casillero(pos_x + cont1, pos_y + cont2);
		}
		cont2 = 0;
		cont1++;
		casillero = this->get_casillero(pos_x + cont1, pos_y + cont2);
	}
	//Si el elemento es un estructural, lo agrego al grafo de conexiones
	if (elemento->es_estructural())
		this->conexiones->agregar_vertice(elemento);
	//Agrego el elemento en la lista de elems
	this->elementos.push_back(elemento);
}

/* Quitar Elemento: */

void Mapa::quitar_elemento(S_ptr<Elemento> elemento){
	//Obtengo la posicion del elemento y su tamaño
	int pos_x = elemento->get_pos_x();
	int pos_y = elemento->get_pos_y();
	int e_ancho = elemento->get_ancho();
	int e_alto = elemento->get_alto();
	int cont1 = 0; int cont2 = 0;
	//Recorro todos los casilleros que ocupa el elemento y lo quito de cada uno de ellos
	S_ptr<Casillero> casillero = this->get_casillero(pos_x, pos_y);
	while ((!casillero.es_nulo()) && (cont1 < e_alto)){
		while ((!casillero.es_nulo()) && (cont2 < e_ancho)){
			if (!elemento->es_estructural())
				casillero->remover_modificador();
			else
				casillero->remover_estructural();
			cont2++;
			casillero = this->get_casillero(pos_x + cont1, pos_y + cont2);
		}
		cont2 = 0;
		cont1++;
		casillero = this->get_casillero(pos_x + cont1, pos_y + cont2);
	}
	//Si el elemento es un estructural, lo quito del grafo de conexiones
	if (elemento->es_estructural())
		this->conexiones->eliminar_vertice(elemento);
	//Quito el elemento de la listas de elementos
	this->elementos.remove(elemento);
}

/* Es Congruente: */

bool Mapa::es_congruente(){
	return true;
}

/* Get Casillero: */

S_ptr<Casillero> Mapa::get_casillero(int pos_x, int pos_y){
	//Si las posiciones recibidas estan dentro de los margenes del mapa devuelvo el casillero
	if (this->validar_coordenadas(pos_x, pos_y))
		return this->mapa[pos_x][pos_y];
	else { //Sino devuelvo un casillero nulo
		S_ptr<Casillero> nulo;
		return nulo;
	}	
}

/* Conectar: */

void Mapa::conectar(S_ptr<Elemento> elem1, S_ptr<Elemento> elem2){
	Obj_Nulo nulo;
	this->conexiones->agregar_arco_no_dirigido(elem1, elem2, nulo, 0);
}

/* Marcar Conectados: */

void Mapa::marcar_conectados(){

}

/* Validar Coordenadas: */

bool Mapa::validar_coordenadas(int x, int y){
	if ((x >= 0) && (y >= 0) && (x < this->alto) && (y < this->ancho))
		return true;
	else
		return false;
}

/* Superficie Disponible: */

bool Mapa::superficie_disponible(int x, int y, int alto, int ancho){
	bool result = true;
	int cont1 = 0; int cont2 = 0;
	//Recorro todos los casilleros de la superficie y me fijo si estan vacios
	S_ptr<Casillero> casillero = this->get_casillero(x, y);
	while ((result) && (cont1 < alto)){
		while ((result) && (cont2 < ancho)){
			if ((casillero.es_nulo()) || (!casillero->get_estructural().es_nulo()))
				result = false;
			cont2++;
			casillero = this->get_casillero(x + cont1, y + cont2);
		}
		cont2 = 0;
		cont1++;
		casillero = this->get_casillero(x + cont1, y + cont2);
	}
	return result;
}

/* Set Salida: */

void Mapa::set_salida(bool estado){
	this->salida = estado;
}

/* Tiene Salida: */

bool Mapa::tiene_salida(){
	return this->salida;
}

/* Set Casa Fantasmas: */

void Mapa::set_casa_fantasmas(bool estado){
	this->casa = estado;
}

/* Tiene Casa Fantasmas: */

bool Mapa::tiene_casa_fantamas(){
	return this->casa;
}

/* ToXML: */
	
S_ptr<TiXmlElement> Mapa::toXml(){
	//Creo un nodo raiz denominado mapa
	S_ptr<TiXmlElement> nodo_raiz = new TiXmlElement("Mapa");
	S_ptr<Elemento> elem;
	//Itero sobre todos los elementos contenidos en el mapa
	list<S_ptr<Elemento> >::iterator it = this->elementos.begin();
	while (it != this->elementos.end()){
		//Por cada elemento, creo un nodo xml
		S_ptr<TiXmlElement> nodo_elem = new TiXmlElement("Elemento");
		//Asigno los atributos del elemento: tipo, orientacion, pos_x, pos_y
		nodo_elem->SetAttribute("Tipo" , (*it)->get_tipo());
		nodo_elem->SetAttribute("Orientacion" , (*it)->get_orientacion());
		nodo_elem->SetAttribute("PosX" , (*it)->get_pos_x());
		nodo_elem->SetAttribute("PosY" , (*it)->get_pos_y());
		//Inserto el nodo de elemento en el nodo raiz (mapa)
		nodo_raiz->InsertEndChild(*nodo_elem);
		it++;
	}
	return nodo_raiz; //Devuelvo el nodo raiz creado
}
