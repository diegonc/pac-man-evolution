//Header
#ifndef Act_Marcas_h_
#define Act_Marcas_h_

//Incluyo las librerias necesarias

#include "elemento.h"
#include "nivel.h"
#include "vista_mapa.h"
#include "../common/smart_pointer.h"
#include "../common/observador.h"
#include "../common/thread.h"
#include "../common/evento.h"
#include "../common/mutex.h"
#include <list>

class VistaMapa;

using namespace std;

/* CLASE ACTUALIZADOR MARCAS: Se encarga de observar a la vista mapa. Cuando se
   agrega un nuevo elemento o se lo remueve, revisa que el nivel activo sea conexo
   y marca los elementos desconectados. */

class ActualizadorMarcas : public Observador, public Thread {
	
	private:
		VistaMapa* vista_mapa; //Vista mapa en la cual graficar
		S_ptr<Nivel> nivel_activo; //Referencia al nivel activo
		S_ptr<Evento> llave; //Permite bloquear y desbloquear al hilo del actualizador de marcas para
						     //realizar esperas pasivas.
		S_ptr<Mutex> mutex; //Mutex para el nivel activo
		bool ejecutando; //Boolean que controla si el actualizador se esta ejecutando o no
	
	public:
		
	/* Constructor: Crea un nuevo actualizador de marcas, que se encarga de observar y graficar sobre
	   la vista mapa pasada por parametro. */
	ActualizadorMarcas(VistaMapa* vista_mapa);
		
	/* Actualizar: Recibe el nivel activo y avisa que algo cambio, para que el hilo
	   del actualizador lo revise. */
	void actualizar(Observable * observable, void * param);
	
	/* Run: El hilo del actualizador se encarga de revisar los elementos desconectados
	   del nivel activo y colocarles una marca en la vista mapa. */
	virtual void run();
	
	/* Get Nivel Activo: Devuelve una referencia al nivel activo en el actualizador. */
	S_ptr<Nivel> get_nivel_activo();
	
	/* Set Nivel Activo: Setea un nuevo nivel activo al actualizador. */
	void set_nivel_activo(S_ptr<Nivel> nivel);
	
	/* Frenar Ejecucion: Frena la ejecucion del actualizador de marcas. */
	void frenar_ejecucion();
	
	/* Esta Ejecutando: Devuelve true si el actualizador se esta ejecutando, false
	   en caso contrario. */
	bool esta_ejecutando();
	
	private:
		
	/* Desmarcar Todos: Se encarga de desmarcar todos los elementos del nivel pasado por parametro, e ir
	   revisando si en el medio se cambio de nivel, en cuyo caso corta el proceso y devuelve false. Si pudo
	   desmarcar todo devuelve true. */
	bool desmarcar_todos(S_ptr<Nivel> nivel);
	
	/* Marcar Desconectados: Se encarga de marcar todos los elementos desconectados del nivel pasado por param, e ir
	   revisando si en el medio se cambio de nivel, en cuyo caso corta el proceso. */
	void marcar_desconectados(S_ptr<Nivel> nivel);

};

#endif
