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
   static int pos=0;
   
   Posicion p;
   
   	if (jugador->get_personaje()->get_tipo() == Personaje::pacman){
		p=get_mundo().get_mapa_activo()->get_salida_pacman()->get_posicion();
		p.set_x(p.get_x() + 0.5);
		p.set_y(p.get_y() + 0.5);
   	}
   	else{
		std::list< S_ptr<EstructuralUnitario> > lista_CasaFantasma=get_mundo().get_mapa_activo()->get_casa_fantasma();	
		pos=pos % lista_CasaFantasma.size();
		std::list< S_ptr<EstructuralUnitario> >::iterator it=lista_CasaFantasma.begin();
		for (int i=0;i<=pos;++i){
			++it;
		}
		S_ptr<EstructuralUnitario> estructural_elegido(*it);
		p=estructural_elegido->get_posicion();
		p.set_x(p.get_x() + 0.5);
		p.set_y(p.get_y() + 0.5);
		++pos;	
   }
   jugador->set_posicion(p);

   Bloqueo b(&llave);		
   jugadores[jugador->get_id()] = jugador;
}

const std::list<Jugador *> ModeloCommon::get_jugadores(){
   std::list<Jugador * > lista_Jug;
   try {
      Bloqueo b(&llave);
      //std::cout << "Entro: " << pthread_self() << std::endl << std::flush;
      //usleep(100);
      std::map<unsigned int, Jugador * >::iterator it;
      it=jugadores.begin();
      while(it!=jugadores.end()){
         Jugador* jug=(*it).second;
         if( jug != NULL )
            lista_Jug.push_back(jug);
         ++it;
      }
      //std::cout << "Salio: " << pthread_self() << std::endl << std::flush;
   } catch (Error::MutexError& e){
       std::cout << "Error en mutex: " << e.what()  << "de: " << pthread_self() << std::endl << std::flush;    
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
