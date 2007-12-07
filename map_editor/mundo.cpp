//Header
#include "mundo.h"

/* CLASE MUNDO: Esta clase representa el mundo, compuesto por niveles. El mismo permite insertar o quitar nuevos
   niveles, reordenarlos, e insertar o quitar elementos estructurales y modificadores en un mapa determinado. */

/* Constructor: */

Mundo::Mundo(){}

/* Destructor: */

Mundo::~Mundo(){
	this->niveles.clear();
}

/* Agregar Nivel: */

int Mundo::agregar_nivel(string nombre, int tam_X, int tam_Y){
	S_ptr<Nivel> nivel (new Nivel(nombre, tam_X, tam_Y));
	this->niveles.push_back(nivel);
	return this->niveles.size();
}

/* Quitar Nivel: */

void Mundo::quitar_nivel(unsigned int nOrden){
	if ((nOrden > 0) && (nOrden <= this->niveles.size())) {
		unsigned int cont = 1;
		list<S_ptr<Nivel> >::iterator it = this->niveles.begin();
		while (cont < nOrden){
			it++;
			cont++;
		}
		this->niveles.erase(it); 
	}
}

/* Agregar Elemento: */

bool Mundo::agregar_elemento(TipoElem tipo, unsigned int nOrden, int posX, int posY, Orientacion orientacion){
	bool result = true;
	if ((nOrden > 0) && (nOrden <= this->niveles.size())){
		unsigned int cont = 1;
		list<S_ptr<Nivel> >::iterator it = this->niveles.begin();
		while (cont < nOrden){
			it++;
			cont++;
		}
		S_ptr<Nivel> nivel = *it;
		result = nivel->agregar_elemento(tipo, posX, posY, orientacion);
	} else
		result = false;
	return result;
}

/* Quitar Elemento: */

bool Mundo::quitar_elemento(unsigned int nOrden, int posX, int posY){
	bool result = true;
	if ((nOrden > 0) && (nOrden <= this->niveles.size())){
		unsigned int cont = 1;
		list<S_ptr<Nivel> >::iterator it = this->niveles.begin();
		while (cont < nOrden){
			it++;
			cont++;
		}
		S_ptr<Nivel> nivel = *it;
		result = nivel->quitar_elemento(posX, posY);
	} else
		result = false;
	return result;
}

/* Get Nivel: */

S_ptr<Nivel> Mundo::get_nivel(unsigned int nOrden){
	S_ptr<Nivel> nivel;
	if ((nOrden > 0) && (nOrden <= this->niveles.size())){
		unsigned int cont = 1;
		list<S_ptr<Nivel> >::iterator it = this->niveles.begin();
		while (cont < nOrden){
			it++;
			cont++;
		}
		nivel = *it;
	}
	return nivel;
}

/* Promover: */

void Mundo::promover(unsigned int nOrden){

}

/* Degradar: */

void Mundo::degradar(unsigned int nOrden){

}

/* Get Cant Niveles: */

unsigned int Mundo::get_cant_niveles(){
	return this->niveles.size();
}

/* ToXML: */

bool Mundo::toXml(char* nombre){
	S_ptr<TiXmlDocument> documento = new TiXmlDocument (nombre);
	if (documento != NULL){
			S_ptr<TiXmlElement> nodo_raiz = new TiXmlElement("Mundo");
			nodo_raiz->SetAttribute ("Cant_Niveles", this->get_cant_niveles());
			S_ptr<Nivel> nivel;
			list<S_ptr<Nivel> >::iterator it = this->niveles.begin();
			int num_nivel = 1;
			while (it != this->niveles.end()){
				S_ptr<TiXmlElement> nodo_nivel = new TiXmlElement("Nivel");
				nodo_nivel->SetAttribute("Numero" , num_nivel);
				nodo_nivel->SetAttribute("Nombre" , ((*it)->get_nombre()).c_str());
				nodo_nivel->SetAttribute("Ancho" , (*it)->get_mapa()->get_ancho());
				nodo_nivel->SetAttribute("Alto" , (*it)->get_mapa()->get_alto());
				nodo_raiz->InsertEndChild(*nodo_nivel);
				(*it)->toXml();
				it++;
				num_nivel++;
			}
			documento->InsertEndChild(*nodo_raiz);
			return documento->SaveFile();
	} else
			return false;
}

/* fromXML: */
	
bool Mundo::fromXml(char* nombre){
	S_ptr<TiXmlDocument> documento = new TiXmlDocument (nombre);
	if ((documento != NULL) && (documento->LoadFile())){
			TiXmlNode* nodo_raiz = documento->RootElement();
			TiXmlNode* nodo_nivel;
			for( nodo_nivel = nodo_raiz->FirstChild(); nodo_nivel != NULL; nodo_nivel = nodo_nivel->NextSibling()) {
					TiXmlElement* xml_elem = dynamic_cast<TiXmlElement*>(nodo_nivel);
					char* nombre_nivel = (char*) xml_elem->Attribute("Nombre");
					int ancho_nivel = 0; 
					int alto_nivel = 0;
					xml_elem->QueryIntAttribute("Ancho", &ancho_nivel);
					xml_elem->QueryIntAttribute("Alto", &alto_nivel);
					this->agregar_nivel(nombre_nivel, alto_nivel, ancho_nivel);
					this->niveles.back()->fromXml();
			}
			return true;
	} else
			return false;
}
