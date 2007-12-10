//Header
#include "act_marcas.h"

/* CLASE ACTUALIZADOR MARCAS: Se encarga de observar a la vista mapa. Cuando se
   agrega un nuevo elemento o se lo remueve, revisa que el nivel activo sea conexo
   y marca los elementos desconectados. */
   
/* Constructor: */

ActualizadorMarcas::ActualizadorMarcas(VistaMapa* vista_mapa){
	this->vista_mapa = vista_mapa;
	this->vista_mapa->agregar_observador(this);
	S_ptr<Evento> nuevo_evento (new Evento());
	S_ptr<Mutex> nuevo_mutex (new Mutex());
	this->llave = nuevo_evento;
	this->mutex = nuevo_mutex;
	this->ejecutando = false;
}
	
/* Actualizar: */

void ActualizadorMarcas::actualizar(Observable * observable, void * param){
	S_ptr<Nivel> nuevo_nivel_activo = *((S_ptr<Nivel>*)param);
	this->set_nivel_activo(nuevo_nivel_activo);
	if (this->llave->esta_esperando())
		this->llave->lanzar_evento();
	usleep(100);
}

/* Run: */

void ActualizadorMarcas::run(){
	this->ejecutando = true;
	while (this->ejecutando){
		S_ptr<Nivel> nivel = this->get_nivel_activo();
		if (!nivel.es_nulo()){
			bool no_error = this->desmarcar_todos(nivel);
			if (no_error) this->marcar_desconectados(nivel);			
		}
		this->llave->esperar_activacion();
	}
}

/* Get Nivel Activo: */

S_ptr<Nivel> ActualizadorMarcas::get_nivel_activo(){
	this->mutex->lock();
		S_ptr<Nivel> nivel = this->nivel_activo;
	this->mutex->unlock();
	return nivel;
}

/* Set Nivel Activo: */

void ActualizadorMarcas::set_nivel_activo(S_ptr<Nivel> nivel){
	this->mutex->lock();
		this->nivel_activo = nivel;
	this->mutex->unlock();
}

/* Frenar Ejecucion: */

void ActualizadorMarcas::frenar_ejecucion(){
	this->ejecutando = false;
	if (this->llave->esta_esperando())
		this->llave->lanzar_evento();
}

/* Esta Ejecutando: */

bool ActualizadorMarcas::esta_ejecutando(){
	return this->ejecutando;
}

/* Desmarcar Todos:  */

bool ActualizadorMarcas::desmarcar_todos(S_ptr<Nivel> nivel){
	list<S_ptr<Elemento> > elementos = nivel->get_mapa()->get_elementos();
	list<S_ptr<Elemento> >::iterator it = elementos.begin();
	bool no_error = true;
	while ((it != elementos.end()) && (no_error)){
		if (nivel == get_nivel_activo()){
			S_ptr<Elemento> elem = (*it);
			if (elem->es_estructural())
				this->vista_mapa->desmarcar_elemento(elem->get_pos_x(), elem->get_pos_y());
		} else
			no_error = false;
		it++;
	}
	return no_error;
}

/* Marcar Desconectados:  */

void ActualizadorMarcas::marcar_desconectados(S_ptr<Nivel> nivel){
	list<S_ptr<Elemento> > desconectados = nivel->get_mapa()->get_desconectados();
	list<S_ptr<Elemento> >::iterator it = desconectados.begin();
	bool no_error = true;
	while ((it != desconectados.end()) && (no_error)){
		if (nivel == get_nivel_activo()){
			S_ptr<Elemento> elem = (*it);
			if (elem->es_estructural())
				this->vista_mapa->marcar_elemento(elem->get_pos_x(), elem->get_pos_y());
		} else
			no_error = false;
		it++;
	}
}
