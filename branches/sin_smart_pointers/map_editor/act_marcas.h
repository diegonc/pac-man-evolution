//Header
#ifndef Act_Marcas_h_
#define Act_Marcas_h_

//Incluyo las librerias necesarias

#include "elemento.h"
#include "nivel.h"
#include "vista_mapa.h"
#include "../common/smart_pointer.h"
#include "../common/observador.h"
#include <list>

class VistaMapa;

using namespace std;

/* CLASE ACTUALIZADOR MARCAS: Se encarga de observar a la vista mapa. Cuando se
   agrega un nuevo elemento o se lo remueve, revisa que el nivel activo sea conexo
   y marca los elementos desconectados. */

class ActualizadorMarcas : public Observador {
	
	private:
		VistaMapa* vista_mapa; //Vista mapa en la cual graficar
		S_ptr<Nivel> nivel_activo; //Referencia al nivel activo
	
	public:
		
	/* Constructor: Crea un nuevo actualizador de marcas, que se encarga de observar y graficar sobre
	   la vista mapa pasada por parametro. */
	ActualizadorMarcas(VistaMapa* vista_mapa);
		
	/* Actualizar: Recibe el nivel activo y se encarga de desmarcar todos los estructurales de es nivel,
	   y luego marcar los que estan desconectados. */
	void actualizar(Observable * observable, void * param);
	
	/* Get Nivel Activo: Devuelve una referencia al nivel activo en el actualizador. */
	S_ptr<Nivel> get_nivel_activo();
	
	/* Set Nivel Activo: Setea un nuevo nivel activo al actualizador. */
	void set_nivel_activo(S_ptr<Nivel> nivel);
	
	private:
		
	/* Desmarcar Todos: Se encarga de desmarcar todos los elementos del nivel pasado por parametro. */
	void desmarcar_todos(S_ptr<Nivel> nivel);
	
	/* Marcar Desconectados: Se encarga de marcar todos los elementos desconectados del nivel pasado por param. */
	void marcar_desconectados(S_ptr<Nivel> nivel);

};

#endif
