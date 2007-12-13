//Header
#include "act_marcas.h"

/* CLASE ACTUALIZADOR MARCAS: Se encarga de observar a la vista mapa. Cuando se
   agrega un nuevo elemento o se lo remueve, revisa que el nivel activo sea conexo
   y marca los elementos desconectados. */
   
/* Constructor: */

ActualizadorMarcas::ActualizadorMarcas(VistaMapa* vista_mapa){
	this->vista_mapa = vista_mapa;
	//Agrego el actualizador como observador de la vista mapa
	this->vista_mapa->agregar_observador(this);
}
	
/* Actualizar: */

void ActualizadorMarcas::actualizar(Observable * observable, void * param){
	//Recibo el nivel por parametro, y si es distinto al nivel contenido
	//en el observador lo seteo como nuevo nivel.
	S_ptr<Nivel> nuevo_nivel_activo = *((S_ptr<Nivel>*)param);
	if (this->get_nivel_activo() != nuevo_nivel_activo)
		this->set_nivel_activo(nuevo_nivel_activo);
	//Si el nuevo nivel no es nulo desmarco todos los elementos y marco los desconectados
	if(!this->get_nivel_activo().es_nulo()){
		this->desmarcar_todos(this->get_nivel_activo());
		this->marcar_desconectados(this->get_nivel_activo());
	}
}

/* Get Nivel Activo: */

S_ptr<Nivel> ActualizadorMarcas::get_nivel_activo(){
	S_ptr<Nivel> nivel = this->nivel_activo;;
	return nivel;
}

/* Set Nivel Activo: */

void ActualizadorMarcas::set_nivel_activo(S_ptr<Nivel> nivel){
	this->nivel_activo = nivel;
}

/* Desmarcar Todos:  */

void ActualizadorMarcas::desmarcar_todos(S_ptr<Nivel> nivel){
	//Obtengo todos los elementos del nivel y utilizando un iterador los recorro
	list<S_ptr<Elemento> > elementos = nivel->get_mapa()->get_elementos();
	list<S_ptr<Elemento> >::iterator it = elementos.begin();
	while (it != elementos.end()){
		//Obtengo cada elemento y si es un estructural lo desmarco
		S_ptr<Elemento> elem = (*it);
		if (elem->es_estructural())
			this->vista_mapa->desmarcar_elemento(elem->get_pos_x(), elem->get_pos_y());
		it++;
	}
}

/* Marcar Desconectados:  */

void ActualizadorMarcas::marcar_desconectados(S_ptr<Nivel> nivel){
	//Obtengo los elementos desconectados del nivel y utilizando un iterador los recorro
	list<S_ptr<Elemento> > desconectados = nivel->get_mapa()->get_desconectados();
	list<S_ptr<Elemento> >::iterator it = desconectados.begin();
	while (it != desconectados.end()){
		//Obtengo cada elemento y si es estructural lo marco
		S_ptr<Elemento> elem = (*it);
		if (elem->es_estructural())
			this->vista_mapa->marcar_elemento(elem->get_pos_x(), elem->get_pos_y());
		it++;
	}
}
