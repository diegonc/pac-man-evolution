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

int Mundo::agregar_nivel(string nombre, int ancho, int alto){
	S_ptr<Nivel> nivel (new Nivel(nombre, ancho, alto));
	this->niveles.push_back(nivel);
	this->set_cambio();
	this->avisar_observadores(NULL);
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
	this->set_cambio();
	this->avisar_observadores(NULL);
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

/* Get Nivel Por Nombre: */

S_ptr<Nivel> Mundo::get_nivel_por_nombre(string nombre){
	S_ptr<Nivel> nivel;
	list<S_ptr<Nivel> >::iterator it = this->niveles.begin();
	while ((it != this->niveles.end()) && (nivel.es_nulo())){
			if (nombre.compare((*it)->get_nombre()) == 0)
				nivel = (*it);
			it++;
	}
	return nivel;
}

/* Promover: */

void Mundo::promover(unsigned int nOrden){
	S_ptr<Nivel> nivel = get_nivel(nOrden);
	if ((nOrden > 1) && (!nivel.es_nulo())){
		this->niveles.remove(nivel);
		unsigned int cont = 1;
		list<S_ptr<Nivel> >::iterator it = this->niveles.begin();
		while (cont < nOrden - 1){
			it++;
			cont++;
		}
		this->niveles.insert(it, nivel);		
	}
	this->set_cambio();
	this->avisar_observadores(NULL);
}

/* Degradar: */

void Mundo::degradar(unsigned int nOrden){
	S_ptr<Nivel> nivel = get_nivel(nOrden);
	if ((nOrden < this->niveles.size()) && (!nivel.es_nulo())){
		this->niveles.remove(nivel);
		unsigned int cont = 1;
		list<S_ptr<Nivel> >::iterator it = this->niveles.begin();
		while (cont < nOrden + 1){
			it++;
			cont++;
		}
		this->niveles.insert(it, nivel);		
	}
	this->set_cambio();
	this->avisar_observadores(NULL);
}

/* Get Cant Niveles: */

unsigned int Mundo::get_cant_niveles(){
	return this->niveles.size();
}

/* Chequear mundo: */

char Mundo::chequear_mundo(int &N_Nivel_incorrecto){
	char error = 0;
	int cont = 1;
	N_Nivel_incorrecto = -1;
	list<S_ptr<Nivel> >::iterator it = this->niveles.begin();
	while ((it != this->niveles.end()) && (!error)){
		S_ptr<Nivel> nivel = (*it);
		if (!nivel->get_mapa()->tiene_salida())	error = 1;
		if (!error)
			if (!nivel->get_mapa()->tiene_casa_fantasmas()) error = 2;
		if (!error)
			if (!nivel->es_congruente()) error = 3;
		if (error) N_Nivel_incorrecto = cont;
		it++;
		cont++;
	}
	return error;
}

/* ToXML: */

bool Mundo::toXml(char* nombre){
	bool no_error = true; //controla que no haya errores
	//Pongo el nombre en un string y busco su extension. Si no la tiene la agrego.
	string filename (nombre);
	if (filename.find(EXT_MUNDO) == string::npos)
		filename += EXT_MUNDO;
	//Intento crear un doc con el filename recien creado
	S_ptr<TiXmlDocument> documento = new TiXmlDocument (filename.c_str());
	//Si se pudo crear el documento
	if (!documento.es_nulo()){
			//Creo un nodo raiz denominado "mundo"
			S_ptr<TiXmlElement> nodo_raiz = new TiXmlElement("Mundo");
			//Le asigno la cantidad de niveles
			nodo_raiz->SetAttribute ("Cant_Niveles", this->get_cant_niveles());
			//Recorro todos los niveles del mundo
			S_ptr<Nivel> nivel;
			list<S_ptr<Nivel> >::iterator it = this->niveles.begin();
			int num_nivel = 1;
			//Recorro hasta alcanzar el ultimo nivel o hasta q haya un error
			while ((it != this->niveles.end()) && (no_error)){
				//Por cada nivel creo un elemento y le pongo como atributos el numero, nombre y tamaño
				S_ptr<TiXmlElement> nodo_nivel = new TiXmlElement("Nivel");
				nodo_nivel->SetAttribute("Numero" , num_nivel);
				nodo_nivel->SetAttribute("Nombre" , ((*it)->get_nombre()).c_str());
				nodo_nivel->SetAttribute("Ancho" , (*it)->get_mapa()->get_ancho());
				nodo_nivel->SetAttribute("Alto" , (*it)->get_mapa()->get_alto());
				//Inserto el "nivel" en el nodo raiz, o sea "mundo"
				nodo_raiz->InsertEndChild(*nodo_nivel);
				//Paso el nivel a un archivo xml
				no_error = (*it)->toXml(nombre);
				it++;
				num_nivel++;
			}
			//Inserto el nodo raiz como hijo del documento
			documento->InsertEndChild(*nodo_raiz);
			//Si no hubo error guardo el archivo
			if (no_error)
				no_error = documento->SaveFile();
			return no_error; //devuelvo el estado de error
	} else
			return false; //Si no se pudo abrir el doc devuelvo false
}

/* fromXML: */
	
bool Mundo::fromXml(char* nombre){
	bool no_error = true; //controla que no haya errores
	//Pongo el nombre en un string y busco su extension. Si no la tiene la agrego.
	string filename (nombre);
	if (filename.find(EXT_MUNDO) == string::npos)
		filename += EXT_MUNDO;
	//Intento abrir un doc con el nombre pasado por parametro
	S_ptr<TiXmlDocument> documento = new TiXmlDocument (filename.c_str());
	//Si se pudo crear el documento y se pudo cargar
	if ((!documento.es_nulo()) && (documento->LoadFile())){
			//Obtengo el nodo raiz
			TiXmlNode* nodo_raiz = documento->RootElement();
			if (nodo_raiz != NULL) {
				//Recorro todos los hijos del nodo raiz, es decir los niveles, hasta que se llegue al ultimo
				//o haya algun error
				TiXmlNode* nodo_nivel = nodo_raiz->FirstChild();
				while ((nodo_nivel != NULL) && (no_error)) {
						//Obtengo los datos del nivel: nombre y tamaño
						TiXmlElement* xml_elem = dynamic_cast<TiXmlElement*>(nodo_nivel);
						char* nombre_nivel = (char*) xml_elem->Attribute("Nombre");
						int ancho_nivel = 0; 
						int alto_nivel = 0;
						xml_elem->QueryIntAttribute("Ancho", &ancho_nivel);
						xml_elem->QueryIntAttribute("Alto", &alto_nivel);
						//Agrego el nivel al mundo
						this->agregar_nivel(nombre_nivel, alto_nivel, ancho_nivel);
						//Cargo el mapa del nivel desde un xml
						no_error = this->niveles.back()->fromXml(nombre);
						//Obtengo el siguiente nivel
						nodo_nivel = nodo_nivel->NextSibling();
				}
				return no_error; //Devuelvo el estado de error
			}	
	}
	return false; //Si hubo algun error devuelvo false
}
