//Header
#ifndef Recorredor_Grafo_h_
#define Recorredor_Grafo_h_

//Incluyo las librerias necesarias
#include <common/smart_pointer.h>
#include <common/grafo.h>
#include <common/vertice.h>
#include <common/arco.h>
#include <editor/obj_nulo.h>
#include <stack>

using namespace std;

/* CLASE RECORREDOR GRAFO: Se encarga de recorrer la componente conexa de un grafo pasado por parametro desde
   un vertice origen determinado, marcando todos los vertices que se visitaron en el recorrido. 
   El dato del vertice debe implementar los metodos marcar(), desmarcar() y esta_marcado(). */

template <class ContenidoVertice, class ContenidoArco> class RecorredorGrafo {
	
	typedef typename list<S_ptr<Arco<ContenidoArco, ContenidoVertice> > >::iterator IteradorArcos;
	typedef typename list<S_ptr<Vertice<ContenidoVertice, ContenidoArco> > >::iterator IteradorVertices;
	
	public:
	
	/* Recorrer Grafo: Recorre una componente conexa del grafo pasado como parametro desde el vertice source tmb pasado por
	   parametro, en profundidad.*/
	
	void recorrer_grafo(Grafo<ContenidoVertice, ContenidoArco>* grafo, S_ptr<Vertice<ContenidoVertice, ContenidoArco> > source){
			S_ptr<Vertice<ContenidoVertice, ContenidoArco> > vertice_actual;
			//Creo una pila para realizar el recorrido
			stack<S_ptr<Vertice<ContenidoVertice, ContenidoArco> > > pila;
			//Desmarco todos los vertices del grafo antes de hacer el recorrido
			this->desmarcar_vertices(grafo);
			//Coloco en la pila el vertice origen
			pila.push(source);
			//Recorro hasta q se vacie la pila
			while (!pila.empty()){
				vertice_actual = pila.top();
				pila.pop();
				//Por cada vertice que obtengo de la pila, si no esta marcado es porque el recorrido recien lo alcanza
				//Lo marco, y apilo los hijos para seguir recorriendo en profundidad
				if (!vertice_actual->get_info()->esta_marcado()){
					vertice_actual->get_info()->marcar();
					this->apilar_hijos(vertice_actual, &pila);
				}					
			}
	}
	
	private:
	
	/* Apilar Hijos: Dados un vertice y una pila, el método apila el vertice y los hijos del mismo en la misma */
	
	void apilar_hijos(S_ptr<Vertice<ContenidoVertice, ContenidoArco> > vertice, stack<S_ptr<Vertice<ContenidoVertice, ContenidoArco> > >* pila){
		//Obtengo los arcos del vertice al cual apilar los hijos
		list<S_ptr<Arco<ContenidoArco, ContenidoVertice> > > aristas = vertice->get_arcos();	
		IteradorArcos it = aristas.begin();
		//Recorro la lista de arcos, obtengo cada destino y lo meto en la pila como hijo del vertice recibido por param.
		while (it != aristas.end()){
			S_ptr<Arco<ContenidoArco, ContenidoVertice> > arista =  (*it);
			S_ptr<Vertice<ContenidoVertice, ContenidoArco> > hijo = arista->get_destino();
			pila->push(hijo);			
			it++;
		}
	}
	
	/* Desmarcar Vertices: Dado el grafo pasado como parametro, el método desmarca todos los vertices del mismo */
	
	void desmarcar_vertices(Grafo<ContenidoVertice, ContenidoArco>* grafo){
		//Obtengo todos los vertices del grafo
		list<S_ptr<Vertice<ContenidoVertice, ContenidoArco> > > vertices = grafo->get_vertices();
		IteradorVertices it = vertices.begin();
		//Los recorro y desmarco cada dato de cada vertice
		while (it != vertices.end()){
			S_ptr<Vertice<ContenidoVertice, ContenidoArco> > vertice_actual =  (*it);
			vertice_actual->get_info()->desmarcar();
			it++;
		}
	}

};

#endif
