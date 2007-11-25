#ifndef CLASS_GRAFO
#define CLASS_GRAFO

/****************************************************************************
-	Esta clase es el grafo. Es el encargado de contener a todos los vertices
	asi como dar una interfaz para poder realizar operaciones sobre el mismo.
-	No se permite el acceso directamente a la lista, debido a que podria estar
	implementado con un mapa, vector u otra cosa.

*****************************************************************************/

#include <list>
#include "vertice.h"
#include "arco.h"
#include "smart_pointer.h"
#include <stdexcept>
#include "comparador.h"
 
template <class ContenidoVertice, class ContenidoArco> class Grafo{
	private:
		//Para simplificar el codigo
		typedef Vertice<ContenidoVertice, ContenidoArco> Clase_Vertice;
		typedef Arco<ContenidoArco, ContenidoVertice> Clase_Arco;		
	
		//Definicion para los iteradores
		typedef typename std::list<S_ptr<Clase_Vertice> >::const_iterator Iterador_Vertice;
		typedef typename std::list<S_ptr<Clase_Arco> >::const_iterator Iterador_Arco;
		//los vertices que posee el grafo
		std::list<S_ptr<Clase_Vertice> > *vertices;
		//constructor de copia privado ya que no quiero que se pase por valor
		Grafo(const Grafo &g){}
					
	public:
		//constructor
		Grafo(){
			//crea la lista
			this->vertices = new list<S_ptr<Clase_Vertice> >();
		}
		//destructor
		~Grafo(){
			//obtengo un iterador de los vertices
			Iterador_Vertice it_vertices = this->get_vertices().begin();
			S_ptr<Clase_Vertice> v_aux;
			//recorro todos los vertices y elimino las aristas, esto es porque
			//como hay referencias circulares entre ambos, pueden quedar objetos
			//colgados que no son detectados por los smart pointers
			while(it_vertices != (this->get_vertices()).end() ){
				v_aux = *it_vertices;
				v_aux->eliminar_arcos_salientes();
				++it_vertices;
			}
			//elimino el contenido de la lista
			this->vertices->clear();	
			//borro la lista
			delete this->vertices;
			
		}
		//agrega un vertice nuevo a la lista de vertices
		
		void agregar_vertice(ContenidoVertice& info){
			S_ptr<Clase_Vertice> vertice_nuevo(new Clase_Vertice(info));
			this->vertices->push_back(vertice_nuevo);
		}
		//busca un vertice comparando el contenido de los mismos.
		S_ptr<Clase_Vertice> buscar_vertice(ContenidoVertice& info_a_buscar){
			bool encontrado = false;
			S_ptr<Clase_Vertice> v_nulo, v_aux;
			Clase_Vertice v_a_buscar(info_a_buscar);	
			
			Iterador_Vertice it = this->get_vertices().begin();
			
			while(!encontrado && this->get_vertices().end() != it ){
				v_aux = *it;
				if( v_a_buscar == *v_aux )
					encontrado = true;
				else
					++it;
			}
			if(encontrado)
				return *it;
			else
				return v_nulo;//devuelvo un objeto nulo
		}
		S_ptr<Clase_Vertice> buscar_vertice(void * info_a_buscar, Comparador *c){
			bool encontrado = false;
			S_ptr<Clase_Vertice> v_aux, v_nulo;
			//creo esta variable, porque voy a usar una referencia, y el valgrind
			//tira un warning debido a que uso el la direccion de la referencia
			//que es temporal
			ContenidoVertice contenido_temporal;
			
			Iterador_Vertice it = this->get_vertices().begin();
			
			while(!encontrado && this->get_vertices().end() != it ){
				v_aux = *it;
				contenido_temporal = v_aux->get_info();
				//este if esta porque se puede optar entre usar un comparador
				//o comparar directamente los vertices. Sirve mas que nada para
				//contenidos del vertice el tipo puntero, en el que muchas veces
				//no tienen mucho sentido comparar punteros
				if( (*c)( &contenido_temporal, info_a_buscar) )
					encontrado = true;
				else
					++it;
			}
			if(encontrado)
				return v_aux;
			else
				return v_nulo;//devuelvo un objeto nulo
		}
		bool esta_vacio(){
			return (this->vertices->size() == 0);
		}
		void agregar_arco_dirigido(ContenidoVertice& origen, ContenidoVertice& destino, ContenidoArco& info, float peso){
			//busca a ver si existen los vertices
			S_ptr<Clase_Vertice> v_origen = buscar_vertice(origen);
			S_ptr<Clase_Vertice> v_destino = buscar_vertice(destino);
			//si existen ambos, agrega el arco
			if(!v_destino.es_nulo() && !v_origen.es_nulo() ){
				S_ptr<Clase_Arco> arco_nuevo(new Clase_Arco(v_origen,v_destino,info));
				arco_nuevo->set_peso(peso);
				v_origen->agregar_arco(arco_nuevo);
			}
			//si no existian lanza una excepcion
			else
				throw std::runtime_error("Vertice inexistente!\n");				
		}
      void agregar_arco_no_dirigido(ContenidoVertice& v1, ContenidoVertice& v2, ContenidoArco& info, float peso){
			agregar_arco_dirigido(v1,v2,info,peso);
		  	agregar_arco_dirigido(v2,v1,info,peso);
						
		}
		//devuelve los vertices vecinos de uno pasado por parametro. En forma de 
		//lista constante
		const list<S_ptr<Clase_Vertice> > get_vertices_vecinos(ContenidoVertice& vertice){
			//creo una lista de vertices
			list<S_ptr<Clase_Vertice> > vecinos;
			
			//busco el vertice
			S_ptr<Clase_Vertice> v = buscar_vertice(vertice);
			//si existia
			if(!vertice.es_nulo()){
				//itero por sus arcos salientes y agrego el destino a la lista
				Iterador_Arco it_arcos = v->get_arcos().begin();		
				while(it_arcos != v->get_arcos().end()){
					S_ptr<Clase_Arco> arco_aux = (*it_arcos);
					vecinos.push_back(arco_aux->get_destino());
					++it_arcos;					
				}
			}
			return vecinos;
			
		}
		//devuelve una lista constante de vertices
		const list<S_ptr<Clase_Vertice> >& get_vertices(){
			return *(this->vertices);
		}
		void eliminar_vertice(ContenidoVertice vertice, Comparador *c=0){
			//obtengo el que voy a eliminar
         S_ptr<Clase_Vertice> v_a_eliminar;
         if( c != 0)			
            v_a_eliminar = buscar_vertice(vertice, c);
			else
            v_a_eliminar = buscar_vertice(vertice);         
			//si no era nulo
			if(!v_a_eliminar.es_nulo()){
				
				Iterador_Vertice it_vertices = this->get_vertices().begin();
				S_ptr<Clase_Vertice> vertice_aux;
				//obtengo todos los vertices del grafo
				while( this->get_vertices().end() != it_vertices ){
					vertice_aux = *it_vertices;
					//obtengo sus aristas salientes
					Iterador_Arco it_arcos = vertice_aux->get_arcos().begin();
					//mientras tenga aristas
					while( vertice_aux->get_arcos().end() != it_arcos ){
						//obtengo la arista
						S_ptr<Clase_Arco> arco_aux = *it_arcos;
						//si el vertice destino es el que se quiere eliminar 
						//elimino la arista para que no quede apuntando a algo 
						//que ya no esta en el grafo
						++it_arcos;
						if( arco_aux->get_destino() == v_a_eliminar)
							vertice_aux->eliminar_arco(arco_aux);
						
					}
					++it_vertices;
				}
				//elimino el vertice
				v_a_eliminar->eliminar_arcos_salientes();
				this->vertices->remove(v_a_eliminar);
			}
			else
				//si no existia lanzo una excepcion
				throw std::runtime_error("El vertice no existe");
		}
};
#endif
