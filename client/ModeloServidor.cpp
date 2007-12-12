#include "ModeloServidor.h"

#include "reloj.h"
#include "PacMan.h"
#include "Fantasma.h"

ModeloServidor::ModeloServidor(){
	//cargar_modelo(); // provisorio
	MundoBasicImp * m = new MundoBasicImp();
	S_ptr<MundoBajoNivel> mundo_default(m);
	this->set_mundo(mundo_default);
	this->parar = false;
}

S_ptr<ModeloServidor> ModeloServidor::instancia;

S_ptr<ModeloServidor> ModeloServidor::get_instancia(){
	if( instancia.es_nulo())
		instancia = S_ptr<ModeloServidor>(new ModeloServidor());
	return instancia;
}

ModeloServidor::~ModeloServidor(){
}

void ModeloServidor::agregar_jugador(Tipo_Jugador jugador){
	
	S_ptr<Personaje> personaje;
	Jugador * j = &(*jugador);
	//si es el primer jugador, le asigno el personaje de pacman, si no
	//fantasma
	if(jugadores.size() == 0)
		personaje = S_ptr<Personaje>(new PacMan(j));
	else
		personaje = S_ptr<Personaje>(new Fantasma(j));
	jugador->set_personaje(personaje);

	this->jugadores.push_back(jugador);
	
}
		
void ModeloServidor::run(){
	
}


