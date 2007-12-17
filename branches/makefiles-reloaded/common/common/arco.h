#ifndef CLASS_ARCO
#define CLASS_ARCO

/**************************************************************************
-	Esta clase representa arco de un grafo. Es direccional en un sentido.
-	Permite cualquier tipo de contenido.
-	Tiene referencias al vertice destino y al vertice origen.
***************************************************************************/

#include "vertice.h"
#include "smart_pointer.h"

//foward declaration para que no haya problemas con el vertice
template <class ContenidoVertice, class ContenidoArco> class Vertice;
class ContenidoVertice;
class ContenidoArco;

template <class ContenidoArco, class ContenidoVertice>class Arco{
	
	private:
		//Para simplificar el codigo
		typedef Vertice<ContenidoVertice, ContenidoArco> Clase_Vertice;	
	
		float peso; //peso del arco
		ContenidoArco info; //contenido "generico" del arco
		S_ptr<Clase_Vertice> destino; //Vertice destino
		S_ptr<Clase_Vertice> origen;  //Vertice origen	
	
	public:
			
	
		//contructor de la clase
		Arco(S_ptr<Clase_Vertice>origen, S_ptr<Clase_Vertice>destino, ContenidoArco& info){
			this->destino = destino;
			this->origen = origen;
			this->set_peso(0);	
			this->set_info(info);
		}
		//constructor de copia
		Arco(const Arco &a){
			this->set_peso(a.get_peso());
			this->origen = a.get_origen();
			this->destino = a.get_destino();
			this->set_info = a.get_info();
		}
		~Arco(){/*No hace nada ya que no hace falta gracias al smart pointer*/};
		//setters y gettters
		void set_peso(float peso){
			this->peso = peso;	
		}
		float get_peso(){
			return this->peso;
		}
		S_ptr<Clase_Vertice> get_destino(){
			return this->destino;
		}
		S_ptr<Clase_Vertice> get_origen(){
			return this->origen;	
		}
		void set_info(ContenidoArco infoNueva){
			this->info = infoNueva;		
		}
		Clase_Vertice get_info(){
			return this->info;		
		}
		//Operadores que definen que se compara por el contenido
		friend bool operator==(Arco<ContenidoArco, ContenidoVertice> &a1, Arco<ContenidoArco, ContenidoVertice> &a2){
			return (a1.get_info() < a2.get_info());
		}
		friend bool operator!=(Arco<ContenidoArco, ContenidoVertice> &a1, Arco<ContenidoArco, ContenidoVertice> &a2){
			return (a1.get_info() != a2.get_info());
		}
		friend bool operator<(Arco<ContenidoArco, ContenidoVertice> &a1, Arco<ContenidoArco, ContenidoVertice> &a2){
			return (a1.get_info() < a2.get_info());
		}
};

#endif
