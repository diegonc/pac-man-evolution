//Header
#include <editor/mundo.h>

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
	//Creo un nuevo nivel con los datos pasados por parametro
	S_ptr<Nivel> nivel (new Nivel(nombre, ancho, alto));
	//Lo agrego al final de la lista y aviso a los observadores que el mundo cambio
	this->niveles.push_back(nivel);
	this->set_cambio();
	this->avisar_observadores(NULL);
	//Devuelvo el orden del nuevo nivel
	return this->niveles.size();
}

/* Quitar Nivel: */

void Mundo::quitar_nivel(unsigned int nOrden){
	//Si el numero de orden es valido
	if ((nOrden > 0) && (nOrden <= this->niveles.size())) {
		//Recorro la lista con un iterador hasta el numero de orden recibido
		unsigned int cont = 1;
		list<S_ptr<Nivel> >::iterator it = this->niveles.begin();
		while (cont < nOrden){
			it++;
			cont++;
		}
		//Borro el elemento en esa posicion
		this->niveles.erase(it); 
	}
	//Aviso a los observadores que el mundo cambio
	this->set_cambio();
	this->avisar_observadores(NULL);
}

/* Agregar Elemento: */

bool Mundo::agregar_elemento(TipoElem tipo, unsigned int nOrden, int posX, int posY, Orientacion orientacion){
	bool result = true; //Vble aux
	//Si el numero de orden es valido
	if ((nOrden > 0) && (nOrden <= this->niveles.size())){
		//Obtengo el nivel en ese orden
		S_ptr<Nivel> nivel = this->get_nivel(nOrden);
		//Agrego el elemento al nivel obtenido
		result = nivel->agregar_elemento(tipo, posX, posY, orientacion);
	} else
		result = false;
	return result;
}

/* Quitar Elemento: */

bool Mundo::quitar_elemento(unsigned int nOrden, int posX, int posY){
	bool result = true; //Vble aux
	//Si el numero de orden es valido
	if ((nOrden > 0) && (nOrden <= this->niveles.size())){
		//Obtengo el nivel en ese orden
		S_ptr<Nivel> nivel = this->get_nivel(nOrden);
		//Quito el elemento del nivel obtenido
		result = nivel->quitar_elemento(posX, posY);
	} else
		result = false;
	return result;
}

/* Get Nivel: */

S_ptr<Nivel> Mundo::get_nivel(unsigned int nOrden){
	//Creo un s_ptr nulo
	S_ptr<Nivel> nivel;
	//Si el numero de orden es valido
	if ((nOrden > 0) && (nOrden <= this->niveles.size())){
		//Recorro la lista con un iterador hasta el numero de orden recibido
		unsigned int cont = 1;
		list<S_ptr<Nivel> >::iterator it = this->niveles.begin();
		while (cont < nOrden){
			it++;
			cont++;
		}
		//Obtengo el nivel en ese orden
		nivel = *it;
	}
	return nivel; //Devuelvo el nivel si se pudo obtener, o el nivel nulo si el nOrden era incorrecto
}

/* Get Nivel Por Nombre: */

S_ptr<Nivel> Mundo::get_nivel_por_nombre(string nombre){
	//Creo un s_ptr nulo
	S_ptr<Nivel> nivel;
	//Creo un iterador de la lista de niveles y la recorro hasta encontrar el nivel con el nombre recibido
	list<S_ptr<Nivel> >::iterator it = this->niveles.begin();
	while ((it != this->niveles.end()) && (nivel.es_nulo())){
			if (nombre.compare((*it)->get_nombre()) == 0)
				nivel = (*it);
			it++;
	}
	return nivel; //Devuelvo el nivel si se pudo obtener, o el nivel nulo si no se encontro
}

/* Promover: */

void Mundo::promover(unsigned int nOrden){
	//Obtengo el nivel a promover
	S_ptr<Nivel> nivel = get_nivel(nOrden);
	//Si no es el primer nivel y existe
	if ((nOrden > 1) && (!nivel.es_nulo())){
		//Lo remuevo de la lista de niveles
		this->niveles.remove(nivel);
		//Calculo la posicion anterior a la que estaba antes
		unsigned int cont = 1;
		list<S_ptr<Nivel> >::iterator it = this->niveles.begin();
		while (cont < nOrden - 1){
			it++;
			cont++;
		}
		//Lo inserto en esta nueva posicion
		this->niveles.insert(it, nivel);	
		//Aviso a los observadores que el mundo cambio
		this->set_cambio();
		this->avisar_observadores(NULL);		
	}
}

/* Degradar: */

void Mundo::degradar(unsigned int nOrden){
	//Obtengo el nivel a degradar
	S_ptr<Nivel> nivel = get_nivel(nOrden);
	//Si no es el ultimo nivel y existe
	if ((nOrden < this->niveles.size()) && (!nivel.es_nulo())){
		//Lo remuevo de la lista de niveles
		this->niveles.remove(nivel);
		//Calculo la posicion posterior a la que estaba antes
		unsigned int cont = 1;
		list<S_ptr<Nivel> >::iterator it = this->niveles.begin();
		while (cont < nOrden + 1){
			it++;
			cont++;
		}
		//Lo inserto en esta nueva posicion
		this->niveles.insert(it, nivel);
		//Aviso a los observadores que el mundo cambio
		this->set_cambio();
		this->avisar_observadores(NULL);		
	}
}

/* Get Cant Niveles: */

unsigned int Mundo::get_cant_niveles(){
	return this->niveles.size();
}

/* Chequear mundo: */

char Mundo::chequear_mundo(int &N_Nivel_incorrecto){
	char error = 0; //Vble que determina el tipo de error encontrado el chequear un nivel deter
	int cont = 1;
	N_Nivel_incorrecto = -1; //Si todos los niveles son correctos esta vble queda en -1
	//Monto un iterador de niveles y recorro los mismo hasta encontrar uno incorrecto o recorrerlos todos
	list<S_ptr<Nivel> >::iterator it = this->niveles.begin();
	while ((it != this->niveles.end()) && (!error)){
		//Obtengo cada nivel
		S_ptr<Nivel> nivel = (*it);
		//Pregunto si tiene salida, si tiene casa de fantasmas y si es congruente
		if (!nivel->get_mapa()->tiene_salida())	error = E_NO_SALIDA_COD;
		if (!error)
			if (!nivel->get_mapa()->tiene_casa_fantasmas()) error = E_NO_CASA_COD;
		if (!error)
			if (!nivel->es_congruente()) error = E_NO_CONGR_COD;
		if (error) N_Nivel_incorrecto = cont; //Si hubo error almaceno el nro de nivel incorrecto
		it++;
		cont++;
	}
	return error; //Devuelvo el cod de error correspondiente
}

/* ToXML: */

bool Mundo::toXml(const char* nombre){
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
	
bool Mundo::fromXml(const char* nombre){
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
						this->agregar_nivel(nombre_nivel, ancho_nivel, alto_nivel);
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
