#ifndef CLASS_S_PTR
#define CLASS_S_PTR

#define NULO 0
/**************************************************************************
-	Esta clase es una implementacion del smart pointer. La idea de la misma
	que un puntero, es decir, almacena referencias a objetos y esta en 
	particular lleva la cuenta de la cantidad de referencias al mismo, 
	que en caso de llegar a cero libera la memoria reservada para el objeto 
	en cuestion.
-	Permite cualquier tipo de contenido.
-	Tiene sobrecargado los operadores * y -> para que se trabaje como si fuera
	el objeto mismo.
***************************************************************************/
#include <stdexcept>
#include "mutex.h"
#include "bloqueo.h"
#include <iostream>

template <class Tipo> class S_ptr{
	protected:
		typedef typename std::runtime_error Runtime_Error;
		
		Tipo* objeto; //objeto que contiene el puntero
		int *cantidad_referencias; //conteo de las referencias para liberar desp.
		Mutex* llave; //esto lo uso para hacerlo thread safety
	
		//devuelve la cantidad de referencias del puntero
		int get_cantidad_referencias(){
         if(this->cantidad_referencias != NULO)
			   return *this->cantidad_referencias;	
         else
            return 0;
		}
		//asigna la cantidad de referencias
		void set_cantidad_referencias(int cant){
         if(this->cantidad_referencias != NULO)			
            *(this->cantidad_referencias) = cant;
		}
		//incremente en 1 la cantidad de referencias
		void incrementar_cantidad_referencias(){
			this->set_cantidad_referencias((this->get_cantidad_referencias())+1);	
		}
		//decrementa en uno la cantidad de referencias
		void decrementar_cantidad_referencias(){
			this->set_cantidad_referencias((this->get_cantidad_referencias())-1);	
		}
		//elimina el objeto, contador y llave - llave viene bloqueada, se desbloquea.
      virtual void eliminar_objeto(){
			if(objeto != NULO){
				//elimina el objeto
				delete this->objeto;
				//setea el objeto como NULO
				this->objeto = NULO;
                                delete this->cantidad_referencias;
                                this->cantidad_referencias = NULO;
				this->llave->unlock();
				delete this->llave;
			}
			//pone la cantidad de referencias en 0
			//this->set_cantidad_referencias(0);
		}
	public:
		/*contructor por defecto que lo pone como nulo, debe usarse para crear
		punteros vacios*/
		S_ptr(){
			this->objeto = NULO;
			this->cantidad_referencias = NULO;
			this->llave = NULO;
		}
		//constructor del objeto
		S_ptr(Tipo *objeto){
			//si no mando NULO como objeto, se lo asigno y le pongo en cant 1
			if(objeto != NULO){
				//se crea el entero que contiene la cantidad de referencias
				// y la llave
				this->cantidad_referencias = new int;
				this->llave = new Mutex();
				this->set_cantidad_referencias(1);
				this->objeto = objeto;	
			}
			else {
				this->cantidad_referencias = NULO;
				this->llave = NULO;
				this->objeto = NULO;
			}
		}
		S_ptr(const S_ptr &p){
			if( ! p.es_nulo() ) {
				Bloqueo b(p.llave);
				//asigno el puntero al nuevo objeto
				this->objeto = p.objeto;
				// copio la llave
				this->llave = p.llave;
				//copio la variable de cantidad de referencias
				this->cantidad_referencias = p.cantidad_referencias;
				//incremento la cantidad de referencias
				this->incrementar_cantidad_referencias();
			} else {
				this->objeto = NULO;
				this->llave = NULO;
				this->cantidad_referencias = NULO;
			}
		}	
		virtual ~S_ptr(){
			if(!this->es_nulo()){
				//bloqueo el elemento para que no hay conflictos entre threads,
				//por ejemplo, que dos decrementen y despues ninguno elimine porque
				//la cantidad de referencias quedo en -1
				this->llave->lock();

				//decrementa la cantidad de referencias
				this->decrementar_cantidad_referencias();
				//si es 0, elimina el objeto y destruye el contador creado
				if( this->get_cantidad_referencias() == 0){
					this->eliminar_objeto();
				}else
					this->llave->unlock();
			}
		}
		//redefine operadores para poder trabajar como un puntero comun, como
		//si fuera del mismo tipo del objeto
		Tipo* operator->(){
			return (this->objeto);
		}
		Tipo& operator*(){
			if(this->objeto != NULO)
				return *(this->objeto);
			else			
				throw Runtime_Error("Acceso a un smart pointer null!!");
			
		}
		bool es_nulo() const {
			return this->objeto == NULO;	
		}
		//operador definido para igualar objetos
		S_ptr<Tipo>& operator=(const S_ptr &p){
			// ignora auto asignacion y asignacion a mismo objeto
			if( (&p != this) && ( this->objeto != p.objeto ) ) {
				// libero la referencia actual
				if( ! es_nulo() ) {
					//thread safety
					this->llave->lock();
					this->decrementar_cantidad_referencias();
					if( this->get_cantidad_referencias() == 0 )
						this->eliminar_objeto();
					else
						this->llave->unlock();
				}
				if( ! p.es_nulo() ) {
					Bloqueo b( p.llave );
					//asigno el puntero al nuevo objeto
					this->objeto = p.objeto;		
					// copio la llave
					this->llave = p.llave;	
					//copio la variable de cantidad de referencias
					this->cantidad_referencias = p.cantidad_referencias;
					//incremento la cantidad de referencias
					this->incrementar_cantidad_referencias();
				} else {
					objeto = NULO;
				       	llave = NULO;
					cantidad_referencias = NULO;
				}
			}
			//devuelvo lo copiado
			return *this;
		}
		//operadores redefinidos
		friend bool operator==(const S_ptr p1, const S_ptr p2) {
			if(p1.objeto == p2.objeto)
				return true;
			else
				return false;
		}
		friend bool operator!=(const S_ptr p1, const S_ptr p2) {
			if(p1.objeto != p2.objeto)
				return true;
			else
				return false;
		}
		friend bool operator<(const S_ptr p1, const S_ptr p2) {
			if(p1.objeto < p2.objeto)
				return true;
			else
				return false;
		}
			
};

#endif
