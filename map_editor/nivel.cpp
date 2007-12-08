//Header
#include "nivel.h"

/* CLASE NIVEL: Esta clase representa un nivel, que contiene un mapa. El mismo permite agregar y quitar elementos
   estructurales y modificadores al mapa, y tambien controlar que tenga una sola componente conexa, marcando los
   casilleros que estan conectados. */

/* Constructor: */

Nivel::Nivel(string nombre, int ancho, int alto){
	this->mapa = new Mapa(ancho, alto);
	this->nombre = nombre;
}

/* Destructor: */

Nivel::~Nivel(){
	delete(this->mapa);
}

/* Agregar Elemento: */

bool Nivel::agregar_elemento(TipoElem tipo, int posX, int posY, Orientacion orientacion){
	bool result = true;
	//Si las posiciones recibidas estan dentro de los margenes del mapa agrego el elemento
	if ((posX >= 0) && (posY >= 0) && (posX < this->mapa->get_ancho()) && (posY < this->mapa->get_alto())){
		S_ptr<Fab_Elementos> fabrica (new Fab_Elementos());
		S_ptr<Elemento> elemento = fabrica->construir(tipo, posX, posY, orientacion);
		if (!elemento.es_nulo())
			result = elemento->agregate(elemento, this->mapa);
		else
			result = false;
	} else
		result = false;
	return result;
}

/* Quitar Elemento: */

bool Nivel::quitar_elemento(int posX, int posY){
	bool result = true;
	//Si las posiciones recibidas estan dentro de los margenes del mapa quito el elemento
	if ((posX >= 0) && (posY >= 0) && (posX < this->mapa->get_ancho()) && (posY < this->mapa->get_alto())){
		S_ptr<Casillero> casillero = this->mapa->get_casillero(posX, posY);
		S_ptr<Elemento> elemento;
		if (casillero->tiene_modificador())
			elemento = casillero->get_modificador();
		else
			elemento = casillero->get_estructural();
		if (!elemento.es_nulo())
			elemento->quitate(elemento, this->mapa);
	} else
		result = false;
	return result;
}

/* Es Congruente: */

bool Nivel::es_congruente(){
	return this->mapa->es_congruente();
}

/* Get Mapa: */

Mapa* Nivel::get_mapa(){
	return this->mapa;
}

/* Set Nombre: */

void Nivel::set_nombre(string nombre){
	this->nombre = nombre;
}
	
/* Get Nombre: */

string Nivel::get_nombre(){
	return this->nombre;
}

/* ToXML: */

bool Nivel::toXml(char* filename_mundo){
	//Paso el filename del mundo a un string y busco su extension. Si esta la remuevo.
	string f_mundo (filename_mundo);
	int pos_ext = f_mundo.find(EXT_MUNDO);
	if ( pos_ext != string::npos)
		f_mundo.erase(pos_ext, pos_ext + 4);
	//Armo el filename del nivel, con el formato especificado
	string filename = f_mundo + "_" + this->get_nombre() + EXT_NIVEL;
	//Creo el documento xml para guardar el nivel
	S_ptr<TiXmlDocument> documento = new TiXmlDocument ((filename).c_str());
	//Si se pudo crear el documento
	if (!documento.es_nulo()){
			//Creo un nodo raiz denominado "nivel"
			S_ptr<TiXmlElement> nodo_raiz = new TiXmlElement("Nivel");
			//Almaceno los atributos del nivel: Nombre, Ancho y Alto
			nodo_raiz->SetAttribute ("Nombre", (this->get_nombre()).c_str());
			nodo_raiz->SetAttribute ("Ancho", this->get_mapa()->get_ancho());
			nodo_raiz->SetAttribute ("Alto", this->get_mapa()->get_alto());
			//Paso el mapa a xml, e inserto su nodo raiz como hijo de "nivel"
			nodo_raiz->InsertEndChild(*(this->get_mapa()->toXml()));
			//Inserto como hijo del archivo al nodo "nivel"
			documento->InsertEndChild(*nodo_raiz);
			//Devuelvo true si el documento se pudo guardar, false en caso contrario
			return documento->SaveFile();
	} else //Si no se pudo crear el doc, devuelvo false
			return false;
}
	
/* FromXML: */

bool Nivel::fromXml(char* filename_mundo){
	//Paso el filename del mundo a un string y busco su extension. Si esta la remuevo.
	string f_mundo (filename_mundo);
	int pos_ext = f_mundo.find(EXT_MUNDO);
	if ( pos_ext != string::npos)
		f_mundo.erase(pos_ext, pos_ext + 4);
	//Armo el filename del nivel, con el formato especificado
	string filename = f_mundo + "_" + this->get_nombre() + EXT_NIVEL;
	//Creo el documento xml para cargar el nivel
	S_ptr<TiXmlDocument> documento = new TiXmlDocument ((filename).c_str());
	//Si se pudo crear el documento y se pudo cargar
	if ((!documento.es_nulo()) && (documento->LoadFile())){
		//Obtengo el nodo raiz del documento (nodo "nivel")
		TiXmlNode* nodo_raiz = documento->RootElement();		
		if (nodo_raiz != NULL) {
			//Obtengo el nodo "mapa"
			TiXmlNode* nodo_mapa = nodo_raiz->FirstChild();
			if (nodo_mapa != NULL){
				//Obtengo todos los hijos del nodo "mapa", es decir los elementos
				TiXmlNode* nodo_nivel;
				for(nodo_nivel = nodo_mapa->FirstChild(); nodo_nivel != NULL; nodo_nivel = nodo_nivel->NextSibling()) {
							//Veo a cada nodo como elemento
							TiXmlElement* xml_elem = dynamic_cast<TiXmlElement*>(nodo_nivel);
							//Obtengo los datos del elemento: tipo, orientacion, pos_x, pos_y
							int tipo_elem = 0;
							xml_elem->QueryIntAttribute("Tipo", &tipo_elem);
							int orientacion = 0;
							xml_elem->QueryIntAttribute("Orientacion", &orientacion);
							int pos_x = 0;
							xml_elem->QueryIntAttribute("PosX", &pos_x);
							int pos_y = 0;
							xml_elem->QueryIntAttribute("PosY", &pos_y);
							//Agrego un elemento con los datos obtenidos
							this->agregar_elemento((TipoElem) tipo_elem, pos_x, pos_y, (Orientacion) orientacion);
				}
				return true; //Si cargo todo devuelvo true
			}
		}
	}
	return false; //Si hubo algun error devuelvo false
}
