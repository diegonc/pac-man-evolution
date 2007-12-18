/******************CLASE WRAPPER******************/

/* Esta clase representa un emboltorio de objetos
   que lleva cuenta de la cantidad de referencias
   a esos objetos, y se encarga de destruirlos
   cuando es el unico que lo referencia. */

/******************* HEADER **********************/

#ifndef Wrapper_h_
#define Wrapper_h_

#include "contador.h"
#include <iostream>
#include <ostream>

using namespace std;

#ifndef NULL
#define NULL 0
#endif

/*************************************************/

/* CLASE WRAPPER */

template <class Tipo> class Wrapper {
	//Atributos
	private:
		Tipo* objeto; //Puntero al objeto contenido en el emboltorio
		Contador* c; //Referencia al contador global de referencias al objeto
	
	public:
		
		/* Constructor sin parametros: Inicializa el wrapper vacio */
		Wrapper () {
			this->objeto = NULL;
			this->c = NULL;
		}
	
		/* Constructor: Inicializa el wrapper con el objeto mandado por 
	       parametro.*/
		Wrapper(Tipo* objeto){
			if (objeto != NULL){
				this->objeto = objeto; //Asigno el objeto a contener
				this->c = new Contador(); //Creo un contador de referencias al objeto
				this->c->incrementar(); //Lo incremento a 1
			} else {
				this->objeto = NULL;
				this->c = NULL;
			}
		}
		
		/* Constructor de Copia: Inicializa el wrapper con el objeto que
		   esta dentro del otro wrapper */
		Wrapper(const Wrapper<Tipo> &w) {
			this->objeto = w.objeto; //Copio la referencia al objeto
			this->c = w.c; //Copio la referencia la contador
			if (this->c != NULL)
				this->c->incrementar(); //Aumento en 1 la cantidad de referencias al objeto
		}
		
		/* Destructor: Elimina una referencia al objeto contenido en el wrapper.
		   Si es la ultima referencia destruye el objeto. */
		~Wrapper() {
			//Si no es un wrapper vacio
			if (this->objeto != NULL){
				this->c->decrementar(); //Decremento en 1 la cantidad de ref al objeto.
				//Si la cant de ref queda en 0 elimino el objeto y el contador
				if (this->c->getValor() == 0){
					delete (this->objeto);
					delete (this->c);
				} 
			}
		}
		
		/* Operador '*': Redefinicion del operador * para que devuelva el objeto
           dentro del wrapper en vez del wrapper.		*/
		Tipo& operator* () const{
			return *(this->objeto);
		}
		
		/* Operador '->': Redefinicion del operador -> para que devuelva una referencia
		    al objeto en vez de al wrapper. */
		Tipo* operator-> () const{
			return this->objeto;
		}
		
		/* Operador '=' : Redefincion del operador = para que realize correctamente una
		   copia. */
		
		Wrapper<Tipo>& operator= (const Wrapper<Tipo> &w) {
			//Si hago algo del tipo w = w devuelvo el mismo objeto
			if (this == &w) return *this;
			//Quito la referencia al objeto que estaba antes en el wrapper
			if (this->objeto != NULL){
				this->c->decrementar();
				if (this->c->getValor() == 0){
					delete (this->objeto);
					delete (this->c);
				}
			}
			//Pongo una nueva referencia al objeto que estaba contenido en w
			this->objeto = w.objeto;
			this->c = w.c;
			if (this->c!=NULL)
				this->c->incrementar();
			return *this;
		}
		
		/* Operador "==": Redefinicion del operador == para que se comparen los
           objetos contenidos en los wrappers.		*/
		
		bool operator==(const Wrapper<Tipo> &w){
				return (*this->objeto == *w.objeto);
		}
		
		/* Operador "!=": Redefinicion del operador != para que se comparen los
           objetos contenidos en los wrappers.		*/
		
		bool operator!=(const Wrapper<Tipo> &w){
				return (*this->objeto != *w.objeto);
		}
		
		/* Es Nulo: Devuelve true si la referencia al objeto contenido es nula
  		   y false en caso contrario.		*/
		bool esNulo() const{
				return (this->objeto == NULL);	
		}
		
		/* Sobrecarga del operador << para que se imprima el objeto contenido. */
		
		friend ostream& operator<< (ostream& stream, const Wrapper<Tipo> &w){
			stream << *(w.objeto);
			return stream;
		}

};

#endif

/*************************************************/
