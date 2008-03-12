#ifndef CLASS_S_PTR_ARRAY
#define CLASS_S_PTR_ARRAY

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
#include <common/smart_pointer.h>

template <class Tipo> class S_ptr_Array : public S_ptr <Tipo>{
	public:
      S_ptr_Array():S_ptr<Tipo>(){}

      S_ptr_Array(Tipo *objeto):S_ptr<Tipo>(objeto){}
   private:
		void eliminar_objeto(){
			if(this->objeto != NULO){
				//elimina el objeto
				delete[] this->objeto;
				//setea el objeto como NULO
				this->objeto = NULO;
			}
			//pone la cantidad de referencias en 0
			this->set_cantidad_referencias(0);
			
		}
};

#endif
