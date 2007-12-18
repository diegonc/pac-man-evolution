#ifndef CLASS_VERTICE
#define CLASS_VERTICE

/**************************************************************************
Esta clase representa el vertice de un grafo. 
Permite cualquier tipo de contenido.
***************************************************************************/
#include <list>
#include "arco.h"
#include "smart_pointer.h"
#include "comparador.h"

using namespace std;
//foward declaration para que no haya problemas con el arco
class ContenidoArco;
class ContenidoVertice;
template <class ContenidoArco, class ContenidoVertice>class Arco;

//defino el tipo tArco para simplificar la sintaxis luego
template <class ContenidoVertice, class ContenidoArco> class Vertice{
		
  	private:
		//Para simplificar el codigo
		typedef Arco<ContenidoArco, ContenidoVertice> Clase_Arco;		
	
		//Define el contenido que posee el vertice
		ContenidoVertice info;
		//Define una lista con los arcos del vertice	
		list<S_ptr<Clase_Arco> > *arcos_salientes;
						
  	public:
	
		//constructor
		Vertice(ContenidoVertice& info){
			this->set_info(info);		
			this->arcos_salientes = new list<S_ptr<Clase_Arco> >();
		}
		//contructor de copia
		Vertice(const Vertice &v){
			this->set_info(v.get_info());		
			this->arcos_salientes = v.arcos_salientes;
		}
		//destructor
		~Vertice(){
			this->eliminar_arcos_salientes();
			delete this->arcos_salientes;
		}
		//elimina todos los arcos salientes del vertice
		void eliminar_arcos_salientes(){
			this->arcos_salientes->clear();		
		}
		//asigna la ingo al vertice
		void set_info(ContenidoVertice infoNueva){
			this->info = infoNueva;		
		}
		//devuelve la info del vertice
		ContenidoVertice get_info(){
			return this->info;		
		}
		//devuelve la lista de arcos del vertice
		list<S_ptr<Clase_Arco> >& get_arcos(){
			return *(this->arcos_salientes);	
		}
		//elimina el arco del vertice
		void eliminar_arco(S_ptr<Clase_Arco>& arco_a_eliminar){
			this->arcos_salientes->remove(arco_a_eliminar);		
		}
		void agregar_arco(S_ptr<Clase_Arco>& arco_a_agregar){
			this->arcos_salientes->push_back(arco_a_agregar);	
		}
		//operadores de comparacion que utilizan la info del vertice
		friend bool operator==(Vertice<ContenidoVertice, ContenidoArco> &v1,Vertice<ContenidoVertice, ContenidoArco> &v2){
			return (v1.get_info() == v2.get_info());
		}
		friend bool operator!=(Vertice<ContenidoVertice, ContenidoArco> &v1,Vertice<ContenidoVertice, ContenidoArco> &v2){
			return (v1.get_info() != v2.get_info());
		}
		friend bool operator<(Vertice<ContenidoVertice, ContenidoArco> &v1, Vertice<ContenidoVertice, ContenidoArco> &v2){
			return (v1.get_info() < v2.get_info());
		}
		
};

#endif
