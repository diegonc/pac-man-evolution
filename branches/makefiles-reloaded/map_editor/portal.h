//Header
#ifndef Portal_h
#define Portal_h

//Incluyo las librerias necesarias
#include "definiciones.h"
#include "estructural.h"
#include "punto.h"

/* CLASE PORTAL: Clase que representa un portal generico, en una orientacion determinada. Hereda de estructural. */

class Portal : public Estructural {

	protected:
		bool estoy_agregado; //Atrib de uso interno para cortar el agregado de los simetricos
							 //(asi un portal agrega al simetrico, y este ultimo no vuelve a agregar al primero)
	public:

	/* Constructor: Inicializa el portal con un tamaño, una orientacion y posicion determinada. */
	Portal (int pos_x, int pos_y, int ancho, int alto, Orientacion orientacion);
	
	/* Defino al destructor como virtual */
	virtual ~Portal(){}
	
	/* Agregate: Dado el mapa pasado por parametro, el elemento verifica si puede insertarse en mismo,en 
	   la posicion con la que fue creado. Si puede, se agrega y se conecta con todos los vecinos.
	   Devuelve true si se pudo agregar, false en caso contrario.
	   En este caso tambien valida que este en un borde del mapa, y agrega al elemento simetrico.	*/
	virtual bool agregate(S_ptr<Elemento> instancia, Mapa* mapa);
	
	/* Quitate: Dado el mapa pasado por parametro, el elemento se encarga de removerse del mismo. 
	   En este caso tambien remueve al simetrico. */
	virtual void quitate(S_ptr<Elemento> instancia, Mapa* mapa);
	
	/* Get Tipo: Devuelve el tipo del elemento */
	virtual TipoElem get_tipo();
		
	/* Get Simetrico: Devuelve el elem simetrico al actual, respecto del mapa pasado por param.
	   Si el elemento simetrico no existe devuelve NULL. */
	S_ptr<Elemento> get_simetrico(Mapa* mapa);
	
	private:
		
	/* Crear Simetrico: Devuelve un nuevo portal simetrico al actual. 
	   Calcula su pos de acuerdo a la pos del elemento actual y el mapa pasado por parametro. */
	virtual S_ptr<Elemento> crear_simetrico (Mapa* mapa) = 0;
	
	/* Agregar Simetrico: Crea un nuevo elemento del tipo portal, simetrico al elem actual, e intenta
	   agregarlo al mapa pasado por param. Si pudo agregarlo devuelve true, de lo contrario devuelve
	   false. */
	bool agregar_simetrico(Mapa* mapa);
	
	/* Quitar Simetrico: Quita el portal simetrico al actual del mapa pasado por param, si existe. 
	   Sino no hace nada. */
	void quitar_simetrico(Mapa* mapa);
	
	/* Get Pos Simetrica: Devuelve la pos simetrica del elem actual, respecto del mapa pasado por param. 
	   Si el elemento no se encuentra en el limite del mapa devuelve null. */
	virtual S_ptr<Punto> get_pos_simetrica(Mapa* mapa) = 0;
	
	/* Estoy en frontera: Devuelve true si el portal esta en la frontera correcta del mapa, false en caso
	   contrario. */
	virtual bool estoy_en_frontera(Mapa* mapa) = 0;
	
	protected:
		
	/* Conectar con Simetrico: Establece un punto de conexion con el elemento simetrico en el mapa pasado
	   por param, y luego lo conecta. */
	virtual void conectar_con_simetrico(S_ptr<Elemento> instancia, S_ptr<Elemento> simetrico, Mapa* mapa);

};

#endif
