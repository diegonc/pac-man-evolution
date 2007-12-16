#include "ModeloCommon.h"

ModeloCommon::ModeloCommon(): llave(true){
	//cargar_modelo(); // provisorio
	MundoBasicImp * m = new MundoBasicImp();
	S_ptr<MundoBajoNivel> mundo_default(m);
	this->set_mundo(mundo_default);

}

void ModeloCommon::set_mundo(S_ptr<MundoBajoNivel> mundo){
	this->mundo = mundo;
	
	//this->mundo->get_mapa_activo().agregar_observador(this);
}
ModeloCommon::~ModeloCommon(){
}

void ModeloCommon::agregar_jugador(Jugador * jugador){
	Bloqueo b(&llave);	
   jugadores[jugador->get_id()] = jugador;
}

const std::list<Jugador *> ModeloCommon::get_jugadores(){
  	Bloqueo b(&llave);
   std::list<Jugador * > lista_Jug;
   std::map<unsigned int, Jugador * >::iterator it;
   it=jugadores.begin();
   while(it!=jugadores.end()){
      Jugador* jug=(*it).second;
      lista_Jug.push_back(jug);
      ++it;
   }
   return lista_Jug;
}

Jugador * ModeloCommon::get_jugador(unsigned int id){   
   Bloqueo b(&llave);
    std::map<unsigned int, Jugador * >::iterator it = jugadores.find(id);
   if( it != jugadores.end())
      return (*it).second;
   else
   	return NULL;
}
void ModeloCommon::quitar_jugador(unsigned int id){
  	Bloqueo b(&llave);
   jugadores.erase (id);     
}
	
MundoBajoNivel& ModeloCommon::get_mundo(){
	return *this->mundo;
}
bool ModeloCommon::esta_terminado(){
	return this->termino;
}
void ModeloCommon::set_cargado(){
	this->set_cambio();
	this->avisar_observadores(NULL);
}
